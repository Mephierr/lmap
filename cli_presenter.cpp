#include "cli_presenter.h"
#include <iostream>

CliPresenter::CliPresenter(IModel* model, OutputFormatter* formatter)
    : model_(model), formatter_(formatter){}
CliPresenter::~CliPresenter() {
    delete model_;
    delete formatter_;
}
void CliPresenter::exec(int argc, char** argv) {
    Ports ports = {1,2,3};
    model_->GetOpenedPorts(1,2);
    std::cout << formatter_->FormatTcpPorts(ports) << std::endl;
}
