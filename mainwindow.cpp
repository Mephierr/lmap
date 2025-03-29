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

void MainWindow::DisplayPorts(QString&& ports_str) {
    ui->OutputTextBrowser->setPlainText(ports_str);
}

void MainWindow::OnGetOpenedPortsClicked() {
    presenter_->OnGetOpenedPortsClicked();
}
MainWindow::~MainWindow() {
    delete ui;
}
