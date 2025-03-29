#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/time.h>

class PortScanner {
public:
    PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs = 200)
        : targetIP_(targetIP), startPort_(startPort), endPort_(endPort), timeoutMs_(timeoutMs) {
        if (startPort_ > endPort_) {
            std::swap(startPort_, endPort_);
        }
    }

    void scan() {
        std::cout << "Scanning " << targetIP_ << " from port " << startPort_ << " to " << endPort_ << "...\n";

        for (int port = startPort_; port <= endPort_; ++port) {
            if (isPortOpen(port)) {
                std::cout << "Port " << port << " is OPEN\n";
                openPorts_.push_back(port);
            }
        }

        printSummary();
    }

    const std::vector<int>& getOpenPorts() const {
        return openPorts_;
    }

private:
    bool isPortOpen(int port) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            handleError("Socket creation failed");
            return false;
        }

        // Устанавливаем таймаут
        struct timeval timeout;
        timeout.tv_sec = timeoutMs_ / 1000;
        timeout.tv_usec = (timeoutMs_ % 1000) * 1000;

        if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) {
            handleError("Failed to set send timeout");
            close(sock);
            return false;
        }

        if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) {
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
                // Порт закрыт или таймаут
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

    void handleError(const std::string& message) {
        std::cerr << "Error: " << message << " (errno: " << errno << " - " << strerror(errno) << ")\n";
    }

    void printSummary() const {
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

    std::string targetIP_;
    int startPort_;
    int endPort_;
    int timeoutMs_;
    std::vector<int> openPorts_;
};

int main() {
    std::string ipAddress;
    int startPort, endPort;

    std::cout << "Enter target IP address: ";
    std::cin >> ipAddress;

    std::cout << "Enter start port: ";
    std::cin >> startPort;

    std::cout << "Enter end port: ";
    std::cin >> endPort;

    PortScanner scanner(ipAddress, startPort, endPort);
    scanner.scan();

    return 0;
}