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
readerChecksums currentReader;
readerChecksums nextReader;
readerChecksums previousReader;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentPage.myPage=currentReader.getFirst();
    nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);

//    song *mySong = new song;

//    mySong->artistName = "Miguel";
//    mySong->songGenre = "xdGenre";
//    mySong->songId = "123";
//    mySong->songLength = "12345";
//    mySong->songName = "Los pollitos";
//    mySong->setText(mySong->songName);

//    QListWidgetItem *newItem1 = new QListWidgetItem;
//    QListWidgetItem *newItem2 = new QListWidgetItem;
//    QListWidgetItem *newItem3 = new QListWidgetItem;
//    QListWidgetItem *newItem4 = new QListWidgetItem;
//    QListWidgetItem *newItem5 = new QListWidgetItem;
//    QListWidgetItem *newItem6 = new QListWidgetItem;
//    QListWidgetItem *newItem7 = new QListWidgetItem;
//    QListWidgetItem *newItem8 = new QListWidgetItem;
//    QListWidgetItem *newItem9 = new QListWidgetItem;
//    QListWidgetItem *newItem10 = new QListWidgetItem;
//    QListWidgetItem *newItem11 = new QListWidgetItem;
//    QListWidgetItem *newItem12 = new QListWidgetItem;
//    QListWidgetItem *newItem13 = new QListWidgetItem;
//    QListWidgetItem *newItem14 = new QListWidgetItem;
//    QListWidgetItem *newItem15 = new QListWidgetItem;
//    QListWidgetItem *newItem16 = new QListWidgetItem;
//    QListWidgetItem *newItem17 = new QListWidgetItem;
//    QListWidgetItem *newItem18 = new QListWidgetItem;
//    QListWidgetItem *newItem19 = new QListWidgetItem;
//    QListWidgetItem *newItem20 = new QListWidgetItem;
//    QListWidgetItem *newItem21 = new QListWidgetItem;
//    QListWidgetItem *newItem22 = new QListWidgetItem;
//    QListWidgetItem *newItem23 = new QListWidgetItem;
//    QListWidgetItem *newItem24 = new QListWidgetItem;
//    QListWidgetItem *newItem25 = new QListWidgetItem;
//    QListWidgetItem *newItem26 = new QListWidgetItem;
//    QListWidgetItem *newItem27 = new QListWidgetItem;
//    QListWidgetItem *newItem28 = new QListWidgetItem;
//    QListWidgetItem *newItem29 = new QListWidgetItem;
//    QListWidgetItem *newItem30 = new QListWidgetItem;
//    QListWidgetItem *newItem31 = new QListWidgetItem;
//    QListWidgetItem *newItem32 = new QListWidgetItem;
//    QListWidgetItem *newItem33 = new QListWidgetItem;
//    QListWidgetItem *newItem34 = new QListWidgetItem;
//    QListWidgetItem *newItem35 = new QListWidgetItem;
//    QListWidgetItem *newItem36 = new QListWidgetItem;
//    newItem1->setText("helloooo");
//    newItem2->setText("helloooo");
//    newItem3->setText("helloooo");
//    newItem4->setText("helloooo");
//    newItem5->setText("helloooo");
//    newItem6->setText("helloooo");
//    newItem7->setText("helloooo");
//    newItem8->setText("helloooo");
//    newItem9->setText("helloooo");
//    newItem10->setText("helloooo");
//    newItem11->setText("helloooo");
//    newItem12->setText("helloooo");
//    newItem13->setText("helloooo");
//    newItem14->setText("helloooo");
//    newItem15->setText("helloooo");
//    newItem16->setText("helloooo");
//    newItem17->setText("helloooo");
//    newItem18->setText("helloooo");
//    newItem19->setText("helloooo");
//    newItem20->setText("helloooo");
//    newItem21->setText("helloooo");
//    newItem22->setText("helloooo");
//    newItem23->setText("helloooo");
//    newItem24->setText("helloooo");
//    newItem25->setText("helloooo");
//    newItem26->setText("helloooo");
//    newItem27->setText("helloooo");
//    newItem28->setText("helloooo");
//    newItem29->setText("helloooo");
//    newItem30->setText("helloooo");
//    newItem31->setText("helloooo");
//    newItem32->setText("helloooo");
//    newItem33->setText("helloooo");
//    newItem34->setText("helloooo");
//    newItem35->setText("helloooo");
//    newItem36->setText("helloooo");


//    ui->lw_song->insertItem(0,newItem1);
//    ui->lw_song->insertItem(0,newItem2);
//    ui->lw_song->insertItem(0,newItem3);
//    ui->lw_song->insertItem(0,newItem4);
//    ui->lw_song->insertItem(0,newItem5);
//    ui->lw_song->insertItem(0,newItem6);
//    ui->lw_song->insertItem(0,newItem7);
//    ui->lw_song->insertItem(0,newItem8);
//    ui->lw_song->insertItem(0,newItem9);
//    ui->lw_song->insertItem(0,newItem10);
//    ui->lw_song->insertItem(0,newItem11);
//    ui->lw_song->insertItem(0,newItem12);
//    ui->lw_song->insertItem(0,mySong);
//    ui->lw_song->insertItem(0,newItem13);
//    ui->lw_song->insertItem(0,newItem14);
//    ui->lw_song->insertItem(0,newItem15);
//    ui->lw_song->insertItem(0,newItem16);
//    ui->lw_song->insertItem(0,newItem17);
//    ui->lw_song->insertItem(0,newItem18);
//    ui->lw_song->insertItem(0,newItem19);
//    ui->lw_song->insertItem(0,newItem20);
//    ui->lw_song->insertItem(0,newItem21);
//    ui->lw_song->insertItem(0,newItem22);
//    ui->lw_song->insertItem(0,newItem23);
//    ui->lw_song->insertItem(0,newItem24);
//    ui->lw_song->insertItem(0,newItem25);
//    ui->lw_song->insertItem(0,newItem26);
//    ui->lw_song->insertItem(0,newItem27);
//    ui->lw_song->insertItem(0,newItem28);
//    ui->lw_song->insertItem(0,newItem29);
//    ui->lw_song->insertItem(0,newItem30);
//    ui->lw_song->insertItem(0,newItem31);
//    ui->lw_song->insertItem(0,newItem32);
//    ui->lw_song->insertItem(0,newItem33);
//    ui->lw_song->insertItem(0,newItem34);
//    ui->lw_song->insertItem(0,newItem35);
//    ui->lw_song->insertItem(0,newItem36);


    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});




//    for (int i = 0; i<25; i++)
//    {
//        ui->lw_song->insertItem(i,mySong);
//    }
}

void MainWindow::pageManager()
{
    log(ui->lw_song->verticalScrollBar()->value())
    if(ui->lw_song->verticalScrollBar()->value()==0)
    {
        previousPage.myPage=previousReader.getPrevious(currentPage.myPage.get(0)->data.songId);
        currentPage.myPage=currentReader.getFirst();
        nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);
    }
    if (ui->lw_song->verticalScrollBar()->value()==12)
    {
        previousPage.myPage=currentPage.myPage;
        currentPage.myPage=nextPage.myPage;
        nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);
    }

}




MainWindow::~MainWindow()
{
    delete ui;
}

