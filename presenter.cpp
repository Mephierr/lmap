#include "presenter.h"
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QStringListModel>
#define MAX_PORT_LENGTH 10
Presenter::Presenter(){}
void Presenter::SetMainWindow(MainWindow* main_window) {
    main_window_ = main_window;
}
void Presenter::SetModel(IModel* model) {
    model_ = model;
}

void Presenter::OnGetOpenedPortsClicked() {
    Ports ports = model_->GetOpenedPorts(1, 2); // #TODO: port range
    QStringList portList;
    for(Port port : ports) {
        char a[MAX_PORT_LENGTH];
        itoa(port, a, MAX_PORT_LENGTH);
        portList.append(a);
    }
    QStringListModel* qports = new QStringListModel();
    qports->setStringList(portList);
    main_window_->DisplayPorts(qports);
}
