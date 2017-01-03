#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <thread>
#include <QFile>
#include <thread>

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
    void create_boat(const string &boat_string);
    void update_boat(const string &boat_string);
    void run_refresh_thread(SocketManager &socketManager);
    ~MainWindow();

private slots:
    void on_webview_load_over();
    void on_listView_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *_ui;
    QWebEngineView _web_view;
    QStringList _values;
    std::vector<Boat*> _boats;
    QStringListModel *_list_model;

    std::thread *_refresh_thread;
    bool _refresh_running;
    void refresh(SocketManager *socketManager);
};

#endif // MAINWINDOW_H
