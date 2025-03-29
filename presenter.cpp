#include "presenter.h"
#include "mainwindow.h"

Presenter::Presenter(){}

void Presenter::SetMainWindow(MainWindow* main_window) {
    main_window_ = main_window;
}
void Presenter::SetModel(IModel* model) {
    model_ = model;
}

void Presenter::OnRandomNumberClicked() {
    main_window_->DisplayNumber(model_->GetRandomNumber());
}
