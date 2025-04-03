#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include <string>
#include <vector>
#include <atomic>

class PortScanner {
public:
    PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs = 200);
    
    void scan();
    const std::vector<int>& getOpenPorts() const;

private:
    bool isPortOpen(int port);
    bool isPortOpenOptimized(int port);
    void handleError(const std::string& message);
    void printSummary() const;
    bool checkSSESupport();
    
    std::string targetIP_;
    int startPort_;
    int endPort_;
    int timeoutMs_;
    std::vector<int> openPorts_;
    bool useOptimizedPath_ = false;
};

#endif // PORTSCANNER_H