#include "modelimpl.h"
#include "portscanner.h"
#include <cstdlib>
#include <ctime>

ModelImpl::ModelImpl() {}
ModelImpl::~ModelImpl() {}

Ports ModelImpl::GetOpenedPorts(const IPAddress& address, Port from, Port to) {
    PortScanner portscanner(address, from, to);
    portscanner.scan();
    Ports ports = portscanner.getOpenPorts();
    return ports;
}
