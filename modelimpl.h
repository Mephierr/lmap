#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "IModel.h"
class ModelImpl : public IModel
{
public:
    ModelImpl();
    int GetRandomNumber();
};

#endif // MODELIMPL_H
