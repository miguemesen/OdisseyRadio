#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "song.h"
#include "readerchecksums.h"
#include "QScrollBar"
#include "page.h"
#define log(x) std::cout<<x<<std::endl;

page previousPage;
page currentPage;
page nextPage;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    song *mySong = new song;

    mySong->artistName = "Miguel";
    mySong->songGenre = "xdGenre";
    mySong->songId = "123";
    mySong->songLength = "12345";
    mySong->songName = "Los pollitos";
    mySong->setText(mySong->songName);

    QListWidgetItem *newItem1 = new QListWidgetItem;
    QListWidgetItem *newItem2 = new QListWidgetItem;
    QListWidgetItem *newItem3 = new QListWidgetItem;
    QListWidgetItem *newItem4 = new QListWidgetItem;
    QListWidgetItem *newItem5 = new QListWidgetItem;
    QListWidgetItem *newItem6 = new QListWidgetItem;
    QListWidgetItem *newItem7 = new QListWidgetItem;
    QListWidgetItem *newItem8 = new QListWidgetItem;
    QListWidgetItem *newItem9 = new QListWidgetItem;
    QListWidgetItem *newItem10 = new QListWidgetItem;
    QListWidgetItem *newItem11 = new QListWidgetItem;
    QListWidgetItem *newItem12 = new QListWidgetItem;
    newItem1->setText("helloooo");
    newItem2->setText("helloooo");
    newItem3->setText("helloooo");
    newItem4->setText("helloooo");
    newItem5->setText("helloooo");
    newItem6->setText("helloooo");
    newItem7->setText("helloooo");
    newItem8->setText("helloooo");
    newItem9->setText("helloooo");
    newItem10->setText("helloooo");
    newItem11->setText("helloooo");
    newItem12->setText("helloooo");


    ui->lw_song->insertItem(0,newItem1);
    ui->lw_song->insertItem(0,newItem2);
    ui->lw_song->insertItem(0,newItem3);
    ui->lw_song->insertItem(0,newItem4);
    ui->lw_song->insertItem(0,newItem5);
    ui->lw_song->insertItem(0,newItem6);
    ui->lw_song->insertItem(0,newItem7);
    ui->lw_song->insertItem(0,newItem8);
    ui->lw_song->insertItem(0,newItem9);
    ui->lw_song->insertItem(0,newItem10);
    ui->lw_song->insertItem(0,newItem11);
    ui->lw_song->insertItem(0,newItem12);
    ui->lw_song->insertItem(0,mySong);

    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});




//    for (int i = 0; i<25; i++)
//    {
//        ui->lw_song->insertItem(i,mySong);
//    }
}

void MainWindow::pageManager()
{
    if(ui->lw_song->verticalScrollBar()->value()==0)
    {
        previousPage.myPage.removeAll();

    }
}

void MainWindow::onAction()
{
    if(ui->lw_song->verticalScrollBar()->value()==7)
    {

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

