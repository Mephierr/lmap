#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "i_model.h"
class ModelImpl : public IModel 
{
public:
    ModelImpl();
    ~ModelImpl() override;
    Ports GetOpenedPorts(const IPAddress& address, Port from, Port to) override;
};

#endif // MODELIMPL_H
