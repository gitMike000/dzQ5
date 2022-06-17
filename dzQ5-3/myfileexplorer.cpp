#include "myfileexplorer.h"

myFileExplorer::myFileExplorer(QWidget *parent) : QWidget(parent)
{
    dirmodel = new QFileSystemModel();
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(QDir::rootPath());

    layout = new QGridLayout(this);


    treeView = new QTreeView(this);
    treeView->setModel(dirmodel);

    filemodel = new QFileSystemModel();
    filemodel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);
    filemodel->setRootPath(QDir::rootPath());


    tabView = new QTableView(this);
    tabView->setModel(filemodel);

    lineEdit = new QLineEdit(this);
    lineEdit->setReadOnly(true);
    lineEdit->setText(QDir::rootPath());

//    connect(treeView,SIGNAL(clicked(QModelIndex)),
//            tabView,SLOT(setRootIndex(QModelIndex)));
//    connect(tabView,SIGNAL(activated(QModelIndex)),
//            treeView,SLOT(setCurrentIndex(QModelIndex)));
    connect(tabView,SIGNAL(activated(QModelIndex)),
            tabView,SLOT(setRootIndex(QModelIndex)));

    connect(treeView,SIGNAL(clicked(QModelIndex)),
            this, SLOT(setTextLineD(QModelIndex)));
    connect(tabView,SIGNAL(activated(QModelIndex)),
            this,SLOT(setTextLineF(QModelIndex)));


    layout->addWidget(lineEdit,0,0,1,3,Qt::AlignTop);
    layout->addWidget(treeView,1,0,1,1,Qt::AlignAbsolute| Qt::AlignLeft);
    layout->addWidget(tabView,1,1,1,2);

    this->setLayout(layout);
}

void myFileExplorer::setTextLineF(QModelIndex fIndex)
{
    QString fPath=filemodel->filePath(fIndex);
    QModelIndex dIndex=dirmodel->setRootPath(fPath);

    lineEdit->setText(fPath);
    treeView->setCurrentIndex(dIndex);
}

void myFileExplorer::setTextLineD(QModelIndex dIndex)
{
    QString dPath=dirmodel->filePath(dIndex);
    QModelIndex fIndex=filemodel->setRootPath(dPath);

    lineEdit->setText(dPath);
    tabView->setRootIndex(fIndex);
}
