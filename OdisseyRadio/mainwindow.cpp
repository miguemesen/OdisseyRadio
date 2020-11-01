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
    log(utf8_text);

    artistManager();



//    QScrollBar* myScroll2 = ui->lw_artists->verticalScrollBar();
//    connect(myScroll2,&QScrollBar::valueChanged,[&]{pageManager();});

//    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
//    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});
}

void MainWindow::pageManager()
{

}

void MainWindow::artistPressed(QListWidgetItem myItem)
{

}


void MainWindow::artistManager()
{
    LinkedList<artist> myList = myArtistFetcher.getArtists(1592);
    for (int i=0; i<10; i++)
    {
        ui->lw_artists->addItem(*myList.get(i)->data.artistName);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

