#ifndef TCPPORTSFORMATTER_H
#define TCPPORTSFORMATTER_H

#include "IModel.h"
#include <string>
class OutputFormatter
{
public:
    OutputFormatter();

    std::string FormatTcpPorts(const Ports& ports);
private:
    std::string FormatHeader(const Ports& ports);
    std::string FormatPort(const Port& port);
};

#endif // TCPPORTSFORMATTER_H
