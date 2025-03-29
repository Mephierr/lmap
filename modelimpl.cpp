#include "modelimpl.h"
#include <cstdlib>
#include <ctime>

ModelImpl::ModelImpl() {}
ModelImpl::~ModelImpl() {}

Ports ModelImpl::GetOpenedPorts(Port from, Port to) {
    return {1,2,3};
}
