#ifndef PORTSCANNER_H
#define PORTSCANNER_H

#include <string>
#include <vector>

class PortScanner {
public:
    PortScanner(const std::string& targetIP, int startPort, int endPort, int timeoutMs = 200);
    
    void scan();  // Остаётся точно такой же как был
    const std::vector<int>& getOpenPorts() const;  // Без изменений

private:
    bool isPortOpen(int port);  // Приватные методы не меняем
    void handleError(const std::string& message);
    void printSummary() const;

    std::string targetIP_;
    int startPort_;
    int endPort_;
    int timeoutMs_;
    std::vector<int> openPorts_;
};

#endif // PORTSCANNER_H