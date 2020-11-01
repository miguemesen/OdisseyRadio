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

    artistManager();

    connect(ui->lw_artists,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(artistPressed(QListWidgetItem*)));


//    QScrollBar* myScroll2 = ui->lw_artists->verticalScrollBar();
//    connect(myScroll2,&QScrollBar::valueChanged,[&]{pageManager();});

//    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
//    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});
}

void MainWindow::pageManager()
{

}

void MainWindow::artistPressed(QListWidgetItem* myItem)
{
    artist* art = static_cast<artist*>(myItem);
    LinkedList<song> myList = *art->songs;

    for (int i=0; i<myList.getSize();i++)
    {
        myList.get(i)->data.setText(myList.get(i)->data.songName);
        ui->lw_song->insertItem(i,&myList.get(i)->data);
    }

}


void MainWindow::artistManager()
{
    LinkedList<artist> myList = myArtistFetcher.getArtists(1592);
    for (int i=0; i<10; i++)
    {
        myList.get(i)->data.setText(*myList.get(i)->data.artistName);
        ui->lw_artists->insertItem(i,&myList.get(i)->data);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

