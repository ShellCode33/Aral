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
    vector<string> result;
    Boat::processBoatString(boat_string, result);

    Boat *boat = new Boat(result.at(0));
    boat->setLocation(stod(result.at(1)), stod(result.at(2)));
    boat->setCap(result.at(3) == "N" ? NORTH : (result.at(3) == "E" ? EAST : (result.at(3) == "W" ? WEST : SOUTH)));
    boat->setTime(result.at(4));

    _boats.push_back(boat);
    _list_model->insertRow(_list_model->rowCount());
    _list_model->setData(_list_model->index(_list_model->rowCount()-1), boat->getName().c_str());
}
