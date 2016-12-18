#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    _list_model = new QStringListModel(this);
    _list_model->setStringList(_values);
    _ui->listView->setModel(_list_model);
    _ui->verticalLayout->addWidget(&_web_view);

    srand(time(NULL));
    //map_refresh();
}

MainWindow::~MainWindow()
{
    for(Boat *boat : _boats)
        delete boat;

    _boats.clear();

    delete _list_model;
    delete _ui;
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    //cout << index << endl;
}

void MainWindow::map_refresh()
{
    string available_colors[] = {"blue", "green", "yellow", "red", "orange", "black", "white", "brown"};
/*
    string url_str =    "https://www.google.com/maps/embed/v1/view"
                        "?key=AIzaSyC1yGPocd2V99epBPnDcagnmpXZbeZ-aF8"
                        "&zoom=18"
                        "&maptype=satellite";


    Boat *boat = _boats.at(0);
        url_str += "&markers=color:";
        url_str += available_colors[rand() % (sizeof(available_colors) / sizeof(available_colors[0]))]; //couleur aléatoire
        url_str += "|label:";
        url_str += boat->getName();
        url_str += "|";
        url_str += to_string(boat->getLatitude());
        url_str += ",";
        url_str += to_string(boat->getLongitude());


    url_str += "&center=16.0,120.0";

    if(_boats.size() > 0)
    {
        url_str += "&center=";
        url_str += to_string(_boats.at(0)->getLatitude());
        url_str += ",";
        url_str += to_string(_boats.at(0)->getLongitude());
    }

    else
        url_str += "&center=19.0,130.0";

    string html =      "<iframe id=\"map\""
                       " style=\"overflow: hidden;\""
                       " width=\"" + to_string(_web_view.width()) + "\""
                       " height=\"" + to_string(_web_view.height()) + "\""
                       " frameborder=\"0\" style=\"border:0\""
                       " src=\"" + url_str + "\" allowfullscreen>"
                       "</iframe>"
                       "<style type=\"text/css\">body { overflow:hidden; }</script>";
*/
    string html = "<html><head></head><body><div id=\"map_wrapper\" style=\"height: 400px;\"><div id=\"map_canvas\" class=\"mapping\" style=\"width: 100%; height: 100%;\"></div></div></body></html>";

    QFile jquery("/home/shellcode/IUT/ProgSystem/Aral/Client/jquery.js");
    jquery.open(QIODevice::ReadOnly);
    QString js_jquery = jquery.readAll();
    jquery.close();

    QFile map_js("/home/shellcode/IUT/ProgSystem/Aral/Client/map.js");
    map_js.open(QIODevice::ReadOnly);
    QString js_map = map_js.readAll();
    map_js.close();

    _web_view.page()->setHtml(html.c_str());
    _web_view.page()->runJavaScript(js_jquery.toStdString().c_str());
    _web_view.page()->runJavaScript(js_map.toStdString().c_str());
}

void MainWindow::create_boat(const string & boat_string)
{
    cout << "Creating boat with : " << boat_string << endl;
    Boat *boat = Boat::create(boat_string);
    _boats.push_back(boat);
    _list_model->insertRow(_list_model->rowCount());
    _list_model->setData(_list_model->index(_list_model->rowCount()-1), boat->getName().c_str());
}
