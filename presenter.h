#ifndef PRESENTER_H
#define PRESENTER_H
#include "IModel.h"
#include <QObject>
class MainWindow;
class Presenter : QObject
{
    Q_OBJECT
public:
    Presenter();

    void SetMainWindow(MainWindow* main_window);
    void SetModel(IModel* model);

    void OnGetOpenedPortsClicked();
private:
    MainWindow* main_window_;
    IModel* model_;
};

#endif // PRESENTER_H
