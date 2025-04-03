#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "cli_presenter.h"
#include "modelimpl.h"
#include "outputformatter.h"
#include "socket.h"
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/time.h>
#include "output_manager.h"
#include "portscanner.h"

int main(int argc, char** argv) {
#ifdef BUILD_WITH_QT
    QApplication a(argc, argv);
    MainWindow window;
    Presenter presenter(new OutputFormatter());
    window.SetPresenter(&presenter);
    presenter.SetMainWindow(&window);
    presenter.SetModel(new ModelImpl());
    window.show();
    return a.exec();
#else
    IModel* model = new ModelImpl();
    OutputFormatter* formatter = new OutputFormatter();
    CliPresenter presenter(model, formatter);
    presenter.exec(argc, argv);
    return 0;
#endif
}
