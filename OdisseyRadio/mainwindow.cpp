#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "song.h"








MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    song *mySongs[10];

    song *mySong = new song;

    mySong->artistName = "Miguel";
    mySong->songGenre = "xdGenre";
    mySong->songId = "123";
    mySong->songLength = "12345";
    mySong->songName = "Los pollitos";
    mySong->setText(mySong->songName);

    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText("helloooo");


    ui->lw_song->insertItem(0,newItem);
    ui->lw_song->insertItem(0,mySong);

//    for (int i = 0; i<25; i++)
//    {
//        ui->lw_song->insertItem(i,mySong);
//    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

