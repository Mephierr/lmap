#include "modelimpl.h"
#include "outputformatter.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);
    MainWindow window;
    Presenter presenter(new OutputFormatter());
    window.SetPresenter(&presenter);
    presenter.SetMainWindow(&window);
    presenter.SetModel(new ModelImpl());
    window.show();
    return a.exec();
}
