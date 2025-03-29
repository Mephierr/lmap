#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::SetPresenter(Presenter* presenter) {
    presenter_ = presenter;
}

void MainWindow::DisplayPorts(QAbstractItemModel* ports) {
    ui->listView->setModel(ports);
}

void MainWindow::OnGetOpenedPortsClicked() {
    presenter_->OnGetOpenedPortsClicked();
}
MainWindow::~MainWindow() {
    delete ui;
}
