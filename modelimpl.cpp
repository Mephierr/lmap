#include "modelimpl.h"
#include <cstdlib>
#include <ctime>

ModelImpl::ModelImpl() {}

int ModelImpl::GetRandomNumber() {
    return rand();
}
