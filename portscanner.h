#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include <string>
#include <vector>

class PortScanner {
public:
    PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs = 200);
    void scan();
    const std::vector<int>& getOpenPorts() const;

private:
    bool isPortOpen(int port);
    void handleError(const std::string& message);
    void printSummary() const;

    std::string targetIP_;
    int startPort_;
    int endPort_;
    int timeoutMs_;
    std::vector<int> openPorts_;
};

#endif // PORTSCANNER_H