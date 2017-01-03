#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow), _refresh_running(false)
{
    _ui->setupUi(this);

    _list_model = new QStringListModel(this);
    _list_model->setStringList(_values);
    _ui->listView->setModel(_list_model);
    _ui->verticalLayout->addWidget(&_web_view);

    srand(time(NULL));

    string html = "<html><head></head><body><div id=\"map_wrapper\" style=\"height: 330px;\"><div id=\"map_canvas\" class=\"mapping\" style=\"width: 100%; height: 100%;\"></div></div></body></html>";
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
    }

    else
        cout << "Can't find clicked boat !" << endl;
}

void MainWindow::on_webview_load_over()
{
    string markers_js = "var markers = [";
    for(Boat *boat : _boats)
    {
        string lat = to_string(boat->getLatitude());
        string longi = to_string(boat->getLongitude());

        //la fonction to_string() met des , pour les doubles plutot que des . il faut donc les remplacer
        if(lat.find(',') != string::npos)
            lat.replace(lat.find(','), 1, ".");

        if(longi.find(',') != string::npos)
            longi.replace(longi.find(','), 1, ".");

        string marker = "['" + boat->getName() + "', " + lat + ", "  + longi + ", '" + boat->capToString() + "', '" + boat->getLastTimeReceiving() + "'],";
        std::cout << "add marker : " << marker << std::endl;
        markers_js += marker;
    }

    markers_js.erase(markers_js.begin()+markers_js.size(), markers_js.end()); //on enlève la dernière virgule
    markers_js += "];";

    QFile jquery("jquery.js");
    jquery.open(QIODevice::ReadOnly);
    QString js_jquery = jquery.readAll();
    js_jquery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    jquery.close();

    QFile map_js("map.js");
    map_js.open(QIODevice::ReadOnly);
    QString js_map = map_js.readAll();
    map_js.close();

    _web_view.page()->runJavaScript(js_jquery.toStdString().c_str()); //on ajoute la librairie jquery
    _web_view.page()->runJavaScript(markers_js.c_str()); // on ajoute les markers (qui sont en fait la representation des bateaux) à faire apparaitre sur la carte
    _web_view.page()->runJavaScript(js_map.toStdString().c_str()); //on lance le js qui gère la position des bateaux sur la map
}

void MainWindow::create_boat(const string & boat_string)
{
    cout << "Creating boat with : " << boat_string << endl;
    Boat *boat = Boat::create(boat_string);
    _boats.push_back(boat);
    _list_model->insertRow(_list_model->rowCount());
    _list_model->setData(_list_model->index(_list_model->rowCount()-1), boat->getName().c_str());
}

void MainWindow::update_boat(const string & boat_string)
{
    vector<string> result;
    Boat::processBoatString(boat_string, result);

    for(Boat *boat : _boats)
    {
        if(boat->getName() == result.at(0)) //boat found
        {
            QLocale c(QLocale::C); //Obligé de passer par la librairie de QT pour la conversion string -> double car en mode release le resultat n'est pas le même qu'en debug
            double lat = c.toDouble(result.at(1).c_str());
            double longi = c.toDouble(result.at(2).c_str());

            boat->setLocation(lat, longi);
            boat->setCap(result.at(3) == "NORTH" ? NORTH : (result.at(3) == "EAST" ? EAST : (result.at(3) == "WEST" ? WEST : SOUTH)));
            boat->setTime(result.at(4));
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
    }
}
