#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QApplication>
#include <QResource>
#include <QLibraryInfo>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->langBox->addItems(QStringList() << "en_EN" << "ru_RU");
    connect(ui->langBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            [=](const QString &str){
                translater.load("switchlang_" + str, ".");
                qtranslator.load("qt_" + str, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
                qApp->installTranslator(&translater);
                qApp->installTranslator(&qtranslator);

                int i = ui->themeBox->currentIndex();
                ui->themeBox->clear();
                ui->themeBox->addItems(QStringList() << tr("Light") << tr("Dark"));
                ui->themeBox->setCurrentIndex(i);
            });
    translater.load(QString("switchlang_") + QLocale::system().name());
    ui->langBox->setCurrentText(QLocale::system().name());
    qApp->installTranslator(&translater);
    ui->newEdit->setText(ui->newButton->shortcut().toString());
    ui->openEdit->setText(ui->openButton->shortcut().toString());
    ui->saveEdit->setText(ui->saveButton->shortcut().toString());
    ui->quitEdit->setText(ui->quitButton->shortcut().toString());

    ui->themeBox->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newButton_clicked()
{
    fileName = "";
    ui->textEdit->clear();
}

void MainWindow::on_saveButton_clicked()
{
    fileName = QFileDialog::getSaveFileName(this,
                                     tr("Save text"), Path+'/'+fileName, (tr("Text Files (*.txt)")),
                                     nullptr, QFileDialog::DontUseNativeDialog);
    if (fileName.length())
    {
        QFile f(fileName + ".txt");
        f.open(QIODevice::WriteOnly);
        QTextStream in (&f);
        in << ui->textEdit->toPlainText();
        f.flush();
        f.close();
    }
}


void MainWindow::on_openButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,
                                     tr("Open text"), Path, (tr("Text Files (*.txt)")),
                                            nullptr, QFileDialog::DontUseNativeDialog );
    if (fileName.length())
    {
        Path = QFileInfo(fileName).path();
        QFile f(fileName);
        f.open(QIODevice::ReadOnly);
        QTextStream in(&f);
        ui->textEdit->setText(in.readAll());
        f.close();
    }
}


void MainWindow::on_helpButton_clicked()
{
    QFile h(":/help/text_"+ui->langBox->currentText());
    h.open(QIODevice::ReadOnly);
    QTextStream in(&h);
    ui->textEdit->setText(in.readAll());
    h.close();
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    ui->textEdit->setReadOnly(checked);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
            ui->retranslateUi(this);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
//    if (event->key() == (Qt::CTRL & Qt::Key_Q))
//    {
//        emit ui->openButton->clicked();//  on_openButton_clicked();
//    }
//    else if (event->key() == (Qt::CTRL & Qt::Key_N))
//    {
//        emit MainWindow::on_newButton_clicked();
//    }
}



void MainWindow::on_quitButton_clicked()
{
    qApp->exit(0);
}


void MainWindow::on_newEdit_textChanged(const QString &arg)
{
    ui->newButton->setShortcut(arg);
}


void MainWindow::on_openEdit_textChanged(const QString &arg)
{
    ui->openButton->setShortcut(arg);
}


void MainWindow::on_saveEdit_textChanged(const QString &arg)
{
    ui->saveButton->setShortcut(arg);
}


void MainWindow::on_quitEdit_textChanged(const QString &arg)
{
    ui->quitButton->setShortcut(arg);
}


void MainWindow::on_themeBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == tr("Light"))
    {
        setStyleSheet("QWidget {background: base; color: base;}");

    }
    else if (arg1 == tr("Dark"))
    {       
      setStyleSheet(" QWidget {color: rgb(2,203,204); background-color: rgb(68,68,68); selection-color: white; selection-background-color: gray;}");
    }
}

