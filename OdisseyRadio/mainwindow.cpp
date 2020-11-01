#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "song.h"
#include "readerchecksums.h"
#include "QScrollBar"
#include "page.h"
#include "fetchartists.h"
#include "LinkedList.h"
#include "artist.h"
#define log(x) std::cout<<x<<std::endl;

//page previousPage;
//page currentPage;
//page nextPage;
//readerChecksums currentReader;
//readerChecksums nextReader;
//readerChecksums previousReader;
fetchArtists myArtistFetcher;



/**
  Starts app and runs it in an event
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lw_song->verticalScrollBar()->setMaximum(23);

    LinkedList<artist> myArtistList;
    myArtistList = myArtistFetcher.getArtists(1592);

    std::string utf8_text = myArtistList.get(9)->data.songs->get(6)->data.songName.toUtf8().constData();
    log(utf8_text)

//    for (int i=0; i<10; i++)
//    {
//        log(*myArtistList.get(i)->data.artistName)
//    }

//    currentPage.myPage=currentReader.getFirst();
//    nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);

//    for (int i=0; i<12; i++) {
//        song *mySong = &nextPage.myPage.get(i)->data;
//        mySong->songName="j";
//        ui->lw_song->insertItem(i,mySong);
//        mySong->setText(mySong->songName);
//    }


//    for (int i=0; i<12; i++)
//    {
//        song *mySong = &currentPage.myPage.get(i)->data;
//        mySong->songName="i";
//        ui->lw_song->insertItem(i,mySong);
//        mySong->setText(mySong->songName);
//    }


//    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
//    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});
}

void MainWindow::pageManager()
{
    //log(ui->lw_song->verticalScrollBar()->value())
//    if(ui->lw_song->verticalScrollBar()->value()==0)
//    {
//        previousPage.myPage=previousReader.getPrevious(currentPage.myPage.get(0)->data.songId);
//        currentPage.myPage=currentReader.getFirst();
//        nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);
//    }
//    if (ui->lw_song->verticalScrollBar()->value()==12)
//    {
//        previousPage.myPage=currentPage.myPage;
//        currentPage.myPage=nextPage.myPage;
//        nextPage.myPage=nextReader.getNext(currentPage.myPage.get(11)->data.songId);
//    }

}





MainWindow::~MainWindow()
{
    delete ui;
}

