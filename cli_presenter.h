#pragma once
#include "i_model.h"
#include "outputformatter.h"

class CliPresenter {
public:
    CliPresenter(IModel* model, OutputFormatter* formatter);
    ~CliPresenter();
    int exec(int argc, char** argv);
private:
    IModel* model_;
    OutputFormatter* formatter_;
};
