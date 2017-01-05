#include "mainwindow.h"
#include "ui_mainwindow.h"

typedef QVector<QVector<int> > fix_bug;

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow),
                                        _refresh_running(false), _is_web_view_loaded(false)
{
    _ui->setupUi(this);

    _list_model = new QStringListModel(this);
    _list_model->setStringList(_values);
    _ui->listView->setModel(_list_model);
    _ui->verticalLayout->addWidget(&_web_view);

    srand(time(NULL));

    qRegisterMetaType<fix_bug>("fix_bug");

    string html = "<html><body><div id=\"map_wrapper\" style=\"height: 330px;\"><div id=\"map_canvas\" class=\"mapping\" style=\"width: 100%; height: 100%;\"></div></div></body></html>";
    _web_view.page()->setHtml(html.c_str());

    connect(&_web_view, SIGNAL(loadFinished(bool)), SLOT(on_webview_load_over()));
}

MainWindow::~MainWindow()
{
    for(Boat *boat : _boats)
        delete boat;

    _boats.clear();

    delete _list_model;
    delete _ui;

    _refresh_running = false; //will stop the refresh thread
}

void MainWindow::on_listView_pressed(const QModelIndex &index)
{
    Boat *clickedBoat = nullptr;

    for(Boat *boat : _boats)
        if(boat->getName() == index.data().toString().toStdString())
        {
            clickedBoat = boat;
            break;
        }

    if(clickedBoat != nullptr)
    {
        cout << "You choose boat : " << clickedBoat->getName() << endl;
        _web_view.page()->runJavaScript(QString::fromStdString("var boat_name = '" + clickedBoat->getName() + "'"));
        _web_view.page()->runJavaScript(QString::fromStdString("var boat_latitude = '" + to_string(clickedBoat->getLatitude()) + "'"));
        _web_view.page()->runJavaScript(QString::fromStdString("var boat_longitude = '" + to_string(clickedBoat->getLongitude()) + "'"));
        _web_view.page()->runJavaScript(QString::fromStdString("var boat_cap = '" + clickedBoat->capToString() + "'"));

        QFile file("on_list_view_clic.js");
        file.open(QIODevice::ReadOnly);
        QString js_updater = file.readAll();
        file.close();
        _web_view.page()->runJavaScript(js_updater);

        string lat = to_string(clickedBoat->getLatitude());
        string longi = to_string(clickedBoat->getLongitude());

        //la fonction to_string() met des , pour les doubles plutot que des . il faut donc les remplacer
        if(lat.find(',') != string::npos)
            lat.replace(lat.find(','), 1, ".");

        if(longi.find(',') != string::npos)
            longi.replace(longi.find(','), 1, ".");

        stringstream show_boat_details;
        show_boat_details << "open(['";
        show_boat_details << clickedBoat->getName() << "', ";
        show_boat_details << lat << ", ";
        show_boat_details << longi << ", '";
        show_boat_details << clickedBoat->capToString() << "', '";
        show_boat_details << clickedBoat->getLastTimeReceiving() << "']);";
        _web_view.page()->runJavaScript(show_boat_details.str().c_str());
    }

    else
        cout << "Can't find clicked boat !" << endl;
}

void MainWindow::on_webview_load_over()
{
    _is_web_view_loaded = true;
    QFile jquery("jquery.js");
    jquery.open(QIODevice::ReadOnly);
    QString js_jquery = jquery.readAll();
    js_jquery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    jquery.close();

    _web_view.page()->runJavaScript(js_jquery.toStdString().c_str()); //on ajoute la librairie jquery

    QFile map_js("map.js");
    map_js.open(QIODevice::ReadOnly);
    QString js_map = map_js.readAll();
    map_js.close();

    _web_view.page()->runJavaScript(js_map.toStdString().c_str()); //on initialise les fonctions et variables utiles
}

void MainWindow::create_boat(const string & boat_string)
{
    cout << "Creating boat with : " << boat_string << endl;
    Boat *boat = Boat::create(boat_string);
    _boats.push_back(boat);
    _list_model->insertRow(_list_model->rowCount());
    _list_model->setData(_list_model->index(_list_model->rowCount()-1), boat->getName().c_str());

    string lat = to_string(boat->getLatitude());
    string longi = to_string(boat->getLongitude());

    //la fonction to_string() met des , pour les doubles plutot que des . il faut donc les remplacer
    if(lat.find(',') != string::npos)
        lat.replace(lat.find(','), 1, ".");

    if(longi.find(',') != string::npos)
        longi.replace(longi.find(','), 1, ".");

    stringstream add_marker_js;
    add_marker_js << "add_marker(['";
    add_marker_js << boat->getName() << "', ";
    add_marker_js << lat << ", ";
    add_marker_js << longi << ", '";
    add_marker_js << boat->capToString() << "', '";
    add_marker_js << boat->getLastTimeReceiving() << "']);";

    _js_commands_queue.push_back(add_marker_js.str());
}

void MainWindow::update_boat(const string & boat_string)
{
    vector<string> result;
    Boat::processBoatString(boat_string, result);

    for(Boat *boat : _boats)
    {
        if(boat->getName() == result.at(0)) //boat found
        {
            //cout << "update " << boat->getName() << endl;
            cout << boat_string << endl;

            QLocale c(QLocale::C);
            double lat = c.toDouble(result.at(1).c_str());
            double longi = c.toDouble(result.at(2).c_str());

            boat->setLocation(lat, longi);
            boat->setCap(result.at(3));
            boat->setTime(result.at(4));

            stringstream add_marker_js;
            add_marker_js << "update_marker(['";
            add_marker_js << boat->getName() << "', ";
            add_marker_js << boat->getLatitude() << ", ";
            add_marker_js << boat->getLongitude() << ", '";
            add_marker_js << boat->capToString() << "', '";
            add_marker_js << boat->getLastTimeReceiving() << "']);";

            _js_commands_queue.push_back(add_marker_js.str());
            break;
        }
    }
}

void MainWindow::run_refresh_thread(SocketManager & socketManager)
{
    _refresh_running = true;
    _refresh_thread = new std::thread(&MainWindow::refresh, this, &socketManager);
    _refresh_thread->detach();
}

void MainWindow::refresh(SocketManager * socketManager)
{
    while(_refresh_running)
    {
        Packet received_packet = socketManager->receive_packet();

        switch (received_packet) {

        case BOAT_CREATED:
            create_boat(socketManager->receive_string());
            break;

        case BOAT_UPDATED:
            update_boat(socketManager->receive_string());
            break;

        default:
            cerr << "Unknown packet" << endl;
            break;
        }

        if(_is_web_view_loaded)
        {
            for(string js_command : _js_commands_queue)
                _web_view.page()->runJavaScript(js_command.c_str());

            _js_commands_queue.clear();
        }
    }
}
