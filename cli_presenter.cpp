#include "cli_presenter.h"
#include <iostream>

CliPresenter::CliPresenter(IModel* model, OutputFormatter* formatter)
    : model_(model), formatter_(formatter){}
CliPresenter::~CliPresenter() {
    delete model_;
    delete formatter_;
}
void CliPresenter::exec(int argc, char** argv) {
    Port from, to;
    if(argc != 4) {
        std::cout << "Usage:$ lmap [IPv4] [from port] [to port]" << std::endl;
        return;
    }
    from = atoi(argv[2]);
    to = atoi(argv[3]);
    Ports ports = model_->GetOpenedPorts(from, to);
    std::cout << formatter_->FormatTcpPorts(ports) << std::endl;
}
