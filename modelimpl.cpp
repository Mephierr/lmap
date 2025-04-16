#include "modelimpl.h"
#include <cstdlib>
#include <ctime>

ModelImpl::ModelImpl() {}
ModelImpl::~ModelImpl() {}

Ports ModelImpl::GetOpenedPorts(const IPAddress& address, Port from, Port to) {
    //aboba
    Ports ports(to - from + 1);
    for(int i = from; i <= to; ++i)
        ports[i - from] = i;
    return ports;
}
