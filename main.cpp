#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "modelimpl.h"
#include "socket.h"
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/time.h>
#include "portscanner.h"
#include "mainwindow.h"

#include <QApplication>

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
