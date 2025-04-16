#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qt_presenter.h"
#include <QMainWindow>
#include <QAbstractItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetPresenter(Presenter* presenter);

    void DisplayPorts(QString&& ports_str);
    QString GetFromPort();
    QString GetToPort();
    QString GetScannedIP();
public slots:
    void OnGetOpenedPortsClicked();

private:
    Ui::MainWindow *ui;

    Presenter* presenter_;
};
#endif // MAINWINDOW_H
