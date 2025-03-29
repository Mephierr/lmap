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

void MainWindow::DisplayNumber(int number) {
    ui->label->setText(std::to_string(number).c_str());
}

void MainWindow::OnRandomNumberClicked() {
    presenter_->OnRandomNumberClicked();
}
MainWindow::~MainWindow() {
    delete ui;
}
