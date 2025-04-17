#include "cli_presenter.h"
#include "socket.h"
#include <iostream>

CliPresenter::CliPresenter(IModel* model, OutputFormatter* formatter)
    : model_(model), formatter_(formatter){}
CliPresenter::~CliPresenter() {
    delete model_;
    delete formatter_;
}
int CliPresenter::exec(int argc, char** argv) {
    sock::initializeSockets();
    Port from, to;
    std::string ipaddress;
    if(argc != 4) {
        std::cout << "Usage:$ lmap [IPv4] [from port] [to port]" << std::endl;
        return -1;
    }
    try {
        ipaddress = argv[1];
        from = atoi(argv[2]);
        to = atoi(argv[3]);
    }
    catch (...) {
        std::cerr << "Port must be an integer" << std::endl;
        sock::destroySockets();
        return 1;
    }
    try{
        Ports ports = model_->GetOpenedPorts(ipaddress, from, to);
        std::cout << formatter_->FormatTcpPorts(ports) << std::endl;
    }   
    catch (std::exception ex) {
        std::cerr << "Failed to scan ports: " << ex.what() << std::endl;
        sock::destroySockets();
        return 2;
    }
    sock::destroySockets();
    return 0;
}
