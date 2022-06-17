#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myfileexplorer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myFileExplorer* fe = new myFileExplorer();
    this->setCentralWidget(fe);
}

MainWindow::~MainWindow()
{
    delete ui;
}

