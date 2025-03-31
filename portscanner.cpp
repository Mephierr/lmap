#include "portscanner.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>

PortScanner::PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs)
    : targetIP_(targetIP), startPort_(startPort), endPort_(endPort), timeoutMs_(timeoutMs) {
    if (startPort_ > endPort_) {
        std::swap(startPort_, endPort_);
    }
}

void PortScanner::scan() {
    std::cout << "Scanning " << targetIP_ << " from port " << startPort_ << " to " << endPort_ << "...\n";

    for (int port = startPort_; port <= endPort_; ++port) {
        if (isPortOpen(port)) {
            std::cout << "Port " << port << " is OPEN\n";
            openPorts_.push_back(port);
        }
    }

    printSummary();
}

const std::vector<int>& PortScanner::getOpenPorts() const {
    return openPorts_;
}

bool PortScanner::isPortOpen(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
#ifdef _WIN_32
    if (sock == INVALID_SOCKET) {
#else
    if(sock < 0) {
#endif
        handleError("Socket creation failed");
        return false;
    }

    struct timeval timeout;
    timeout.tv_sec = timeoutMs_ / 1000;
    timeout.tv_usec = (timeoutMs_ % 1000) * 1000;

    if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout))) {
        handleError("Failed to set send timeout");
        close(sock);
        return false;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout))) {
        handleError("Failed to set receive timeout");
        close(sock);
        return false;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, targetIP_.c_str(), &serverAddr.sin_addr) <= 0) {
        handleError("Invalid address / Address not supported");
        close(sock);
        return false;
    }

    int result = connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result < 0) {
        if (errno == ECONNREFUSED || errno == ETIMEDOUT) {
            close(sock);
            return false;
        }
        handleError("Connection failed");
        close(sock);
        return false;
    }

    close(sock);
    return true;
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