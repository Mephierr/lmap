#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "IModel.h"
class ModelImpl : public IModel
{
public:
    ModelImpl();
    ~ModelImpl() override;
    Ports GetOpenedPorts(Port from, Port to) override;
};

#endif // MODELIMPL_H
