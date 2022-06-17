#ifndef MYFILEEXPLORER_H
#define MYFILEEXPLORER_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QLineEdit>
#include <QTableView>
#include <QGridLayout>

class myFileExplorer : public QWidget
{
    Q_OBJECT
public:
    explicit myFileExplorer(QWidget *parent = nullptr);

private:
    QFileSystemModel* dirmodel;
    QFileSystemModel* filemodel;

    QGridLayout* layout;
    QTreeView* treeView;
    QLineEdit* lineEdit;
    QTableView* tabView;

signals:

private slots:
    void setTextLineF(QModelIndex fIndex);
    void setTextLineD(QModelIndex dIndex);

};

#endif // MYFILEEXPLORER_H
