#include "outputformatter.h"
#include <sstream>

OutputFormatter::OutputFormatter() {}

std::string OutputFormatter::FormatTcpPorts(const Ports& ports) {
    std::stringstream ss;
    ss << FormatHeader(ports);
    for(const Port& port : ports) {
        ss << FormatPort(port);
    }
    return ss.str();
}

std::string OutputFormatter::FormatHeader(const Ports& ports) {
    std::stringstream ss;
    if(ports.empty()) {
        ss << "No active ports on current IP.";
        return ss.str();
    }
    ss << "Found " << ports.size() << " active ports: " << std::endl;
    return ss.str();
}
std::string OutputFormatter::FormatPort(const Port& port) {
    std::stringstream ss;
    ss << port << "/tcp\topen" << std::endl;
    return ss.str();
}
