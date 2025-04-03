#pragma once
#include "i_model.h"
#include "outputformatter.h"

class CliPresenter {
public:
    CliPresenter(IModel* model, OutputFormatter* formatter);
    ~CliPresenter();
    void exec(int argc, char** argv);
private:
    IModel* model_;
    OutputFormatter* formatter_;
};
