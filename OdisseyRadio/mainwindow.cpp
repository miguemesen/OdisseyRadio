#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "song.h"
#include "readerchecksums.h"
#include "QScrollBar"
#include "page.h"
#include "fetchartists.h"
#include "LinkedList.h"
#include "artist.h"
#include "loadtrack.h"
#define log(x) std::cout<<x<<std::endl;

readerChecksums myRC;
fetchArtists* myArtistFetcher = new fetchArtists();
int position = 1592;
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

    artistManager();

    connect(ui->lw_artists,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(artistPressed(QListWidgetItem*)));

    connect(ui->btn_play,SIGNAL(clicked()),this,SLOT(playPressed()));



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
    ui->lw_song->clear();
    current_artist = myItem->text().toUtf8().constData();
    for(int i=0; i< myArtistFetcher->artist_list[current_artist]->songs->getSize(); i++)
    {

        song currentSong = myArtistFetcher->artist_list[current_artist]->songs->get(i)->data;
        ui->lw_song->insertItem(i, currentSong.songName.toUtf8().constData());
    }
}

void MainWindow::playPressed()
{

    current_songName = ui->lw_song->currentItem()->text().toUtf8().constData();
    LinkedList<song>* song_list = myArtistFetcher->artist_list[current_artist]->songs;



    song current_song;
    for(int i=0; i < song_list->getSize(); i++){
        song current = song_list->get(i)->data;
        std::string songName = current.artistName.toUtf8().constData();
        if(current_songName.compare(songName)){
            current_song = current;
            log(songName.compare(current_songName))
            log(current_song.songName.toUtf8().constData());
            log(current_songName);
            break;
        }
    }


    std::string id = std::to_string(current_song.songId);
    std::string path = myRC.getSongPathById(id);
    log(path);
    LoadTrack().playMusic(path);



}


void MainWindow::artistManager()
{

    //LinkedList<artist> myList = myArtistFetcher.getArtists(1592); cuando fetchartist no devolvia un puntero
    //LinkedList<artist>* myList = new LinkedList<artist>;

    myArtistFetcher->getArtists(::position);

    for (int i=0; i<10; i++)
    {
        //myList->get(i)->data.setText(*myList->get(i)->data.artistName);
        //ui->lw_artists->insertItem(i,&myList->get(i)->data);
    }


    int index = 0;
    for(std::map<std::string,artist*>::iterator it= myArtistFetcher->artist_list.begin(); it != myArtistFetcher->artist_list.end(); it++)
    {
        //it->second->setText(*it->second->artistName);
        ui->lw_artists->insertItem(index, *it->second->artistName);
        index++;
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

