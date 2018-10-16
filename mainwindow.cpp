#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pushButton_clicked()
{
    QFile file;
    globalPath = QFileDialog::getOpenFileName(nullptr,"","C:/Users/Administrator/Documents/Qt Projects/JSON_Qt","");
    file.setFileName(globalPath);
    if(file.open(QIODevice::ReadOnly|QFile::Text))
    {
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
    }
    file.close();

    QStandardItemModel* model = new QStandardItemModel(nullptr);
    model->setHorizontalHeaderLabels(QStringList()<<"Nume"<<"Varsta"<<"Telefon"<<"Adresa");

    QStandardItem* item_col_1 = new QStandardItem(doc.object().value("Nume").toString());
    QStandardItem* item_col_2 = new QStandardItem(QString::number(doc.object().value("Varsta").toInt()));
    QStandardItem* item_col_3 = new QStandardItem(doc.object().value("Telefon").toString());
    QStandardItem* item_col_4 = new QStandardItem(doc.object().value("Adresa").toString());

    model->appendRow(QList<QStandardItem*>()<<item_col_1<<item_col_2<<item_col_3<<item_col_4);

    ui->tableView->setModel(model);
}
