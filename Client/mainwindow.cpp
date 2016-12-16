#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    QStringList values;

    for(int i = 0; i < 20; i++)
    {
        values << "Bateau " + QString::number(i+1);
    }

    _listModel = new QStringListModel();
    _listModel->setStringList(values);

    _ui->listView->setModel(_listModel);

    _webView = new QWebEngineView();
    _webView->load(QUrl("https://www.google.fr/maps/place/Village+6+IUT/@44.791439,-0.6151907,17z/data=!3m1!4b1!4m5!3m4!1s0xd54d8bd0c8168e3:0x2c2ec4ab546c2805!8m2!3d44.791439!4d-0.613002?hl=en"));

    _ui->verticalLayout->addWidget(_webView);
}

MainWindow::~MainWindow()
{
    delete _ui;
}
