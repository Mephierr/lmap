#include "portscanner.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include "socket.h"
#include <algorithm>

// Проверка поддержки SSE4.2
#ifdef __x86_64__
#include <cpuid.h>
bool PortScanner::checkSSESupport() {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);
    return (ecx & (1 << 20)); // SSE4.2 bit
}
#else
bool PortScanner::checkSSESupport() {
    return false;
}
#endif

PortScanner::PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs)
    : targetIP_(targetIP), startPort_(startPort), endPort_(endPort), timeoutMs_(timeoutMs) {
    if (startPort_ > endPort_) {
        std::swap(startPort_, endPort_);
    }
    useOptimizedPath_ = checkSSESupport();
}

void PortScanner::scan() {
    std::cout << "Scanning " << targetIP_ << " from port " << startPort_ << " to " << endPort_ << "...\n";
    std::cout << "Using optimized path: " << (useOptimizedPath_ ? "YES" : "NO") << "\n";

    for (int port = startPort_; port <= endPort_; ++port) {
        bool isOpen = useOptimizedPath_ ? isPortOpenOptimized(port) : isPortOpen(port);
        if (isOpen) {
            std::cout << "Port " << port << " is OPEN\n";
            openPorts_.push_back(port);
        }
    }

    printSummary();
}

bool PortScanner::isPortOpen(int port) {
    // Стандартная реализация
    int sock = sock::socketInitNonblock(AF_INET, SOCK_STREAM, 0);
    if (sock::isFailure(sock)) {
        handleError("Socket creation failed");
        return false;
    }

    struct timeval timeout;
    timeout.tv_sec = timeoutMs_ / 1000;
    timeout.tv_usec = (timeoutMs_ % 1000) * 1000;

    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, targetIP_.c_str(), &serverAddr.sin_addr) <= 0) {
        sock::socketDestroy(sock);
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        sock::socketDestroy(sock);
        return false;
    }

    sock::socketDestroy(sock);
    return true;
}

#ifdef __SSE4_2__ 
#include <immintrin.h>
bool PortScanner::isPortOpenOptimized(int port) {
    // Оптимизированная реализация с SSE4.2
    int sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (sock::isFailure(sock)) {
        handleError("Socket creation failed");
        return false;
    }

    // Быстрое заполнение структуры с помощью SSE
    __m128i zero = _mm_setzero_si128();
    alignas(16) struct sockaddr_in serverAddr;
    _mm_store_si128((__m128i*)&serverAddr, zero);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = _mm_extract_epi16(_mm_set1_epi16(port), 0);

    // Быстрое преобразование IP
    __m128i ip_addr = _mm_setzero_si128();
    if (_mm_extract_epi32(_mm_cvtsi32_si128(
        inet_pton(AF_INET, targetIP_.c_str(), &serverAddr.sin_addr)), 0) <= 0) {
        sock::socketDestroy(sock);
        return false;
    }

    // Установка таймаутов
    struct timeval tv = {
        .tv_sec = timeoutMs_ / 1000,
        .tv_usec = (timeoutMs_ % 1000) * 1000
    };
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    // Non-blocking connect
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        if (errno != EINPROGRESS) {
            sock::socketDestroy(sock);
            return false;
        }

        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sock, &fdset);

        if (select(sock + 1, nullptr, &fdset, nullptr, &tv) == 1) {
            int so_error;
            socklen_t len = sizeof(so_error);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
            sock::socketDestroy(sock);
            return so_error == 0;
        }
    }

    sock::socketDestroy(sock);
    return true;
}
#else
bool PortScanner::isPortOpenOptimized(int port) {
    // Фолбэк на стандартную реализацию если SSE не поддерживается
    return isPortOpen(port);
}
#endif

// Остальные методы без изменений
const std::vector<int>& PortScanner::getOpenPorts() const {
    return openPorts_;
}

void PortScanner::handleError(const std::string& message) {
    std::cerr << "Error: " << message << " (errno: " << errno << " - " << strerror(errno) << ")\n";
}

void PortScanner::printSummary() const {
    std::cout << "\nScan completed.\n";
    std::cout << "Scanned ports: " << (endPort_ - startPort_ + 1) << "\n";
    std::cout << "Open ports found: " << openPorts_.size() << "\n";

    if (!openPorts_.empty()) {
        std::cout << "List of open ports: ";
        for (int port : openPorts_) {
            std::cout << port << " ";
        }
        std::cout << "\n";
    }
}
