#include "mainwindow.h"
#include "ui_mainwindow.h"
//integriert das MainWindow als Form
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
