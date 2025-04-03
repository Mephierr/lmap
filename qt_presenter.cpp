#include "qt_presenter.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QStringListModel>
#define MAX_PORT_LENGTH 10
Presenter::Presenter(OutputFormatter* formatter)
    : output_formatter_(formatter){}
Presenter::~Presenter() {
    delete model_;
    delete output_formatter_;
}
void Presenter::SetMainWindow(MainWindow* main_window) {
    main_window_ = main_window;
}
void Presenter::SetModel(IModel* model) {
    model_ = model;
}

void Presenter::OnGetOpenedPortsClicked() {
    Ports ports = model_->GetOpenedPorts(1, 2); // #TODO: port range
    std::string output = output_formatter_->FormatTcpPorts(ports);
    QString qoutput(output.c_str());
    main_window_->DisplayPorts(std::move(qoutput));
}
