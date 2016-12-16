#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

#include "socketmanager.h"
#include "../Common/boat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    QWebEngineView *_webView;
    QStringListModel *_listModel;
    SocketManager _socketManager;
    std::vector<Boat> _boats;
};

#endif // MAINWINDOW_H
