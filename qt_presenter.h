#ifndef PRESENTER_H
#define PRESENTER_H
#include "i_model.h"
#include "outputformatter.h"
#include <QObject>
class MainWindow;
class Presenter : QObject
{
    Q_OBJECT
public:
    Presenter(OutputFormatter* formatter);
    ~Presenter();

    void SetMainWindow(MainWindow* main_window);
    void SetModel(IModel* model);

    void OnGetOpenedPortsClicked();
private:
    MainWindow* main_window_;
    IModel* model_; // owns
    OutputFormatter* output_formatter_; // owns
};

#endif // PRESENTER_H
