#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _list_model = new QStringListModel(this);
    _list_model->setStringList(_values);
    _ui->listView->setModel(_list_model);

    _web_view.load(QUrl("https://www.google.fr/maps/place/Village+6+IUT/@44.791439,-0.6151907,17z/data=!3m1!4b1!4m5!3m4!1s0xd54d8bd0c8168e3:0x2c2ec4ab546c2805!8m2!3d44.791439!4d-0.613002?hl=en"));

    _ui->verticalLayout->addWidget(&_web_view);
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    //cout << index << endl;
}

void MainWindow::create_boat(const string & boat_string)
{
    cout << "Creating boat with : " << boat_string << endl;
    _boats.push_back(Boat(boat_string));
    _values << boat_string.c_str();
}
