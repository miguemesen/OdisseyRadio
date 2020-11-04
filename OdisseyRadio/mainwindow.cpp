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
#include <string.h>
#include <QMessageBox>
#define log(x) std::cout<<x<<std::endl;


#define SONG_NOT_FOUND ""
#define CURRENT_SONG_NAME_NOT_ASSIGNED ""

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

    QScrollBar* myScroll2 = ui->lw_artists->verticalScrollBar();
    connect(myScroll2,&QScrollBar::valueChanged,[&]{pageManager();});

//    QScrollBar* myScroll = ui->lw_song->verticalScrollBar();
//    connect(myScroll,&QScrollBar::valueChanged,[&]{pageManager();});

}

void MainWindow::pageManager()
{
    log(ui->lw_artists->verticalScrollBar()->value());
//    if (ui->lw_artists->verticalScrollBar()->value() == 3)
//    {
//        log("Max")
//    }
//    if (ui->lw_artists->verticalScrollBar()->value() == 0)
//    {
//        log("Min")
//    }
}

void MainWindow::artistManager()
{
    myArtistFetcher->getArtists(::position);
    int index = 0;
    for(std::map<std::string,artist*>::iterator it= myArtistFetcher->artist_list.begin(); it != myArtistFetcher->artist_list.end(); it++)
    {
        ui->lw_artists->insertItem(index, QString::fromStdString(it->second->artistName));
        index++;
    }
}

void MainWindow::artistPressed(QListWidgetItem* myItem)
{
    ui->lw_song->clear();
    current_artist = myItem->text().toUtf8().constData();
    for(int i=0; i< myArtistFetcher->artist_list[current_artist]->songs->getSize(); i++)
    {

        song currentSong = myArtistFetcher->artist_list[current_artist]->songs->get(i)->data;
        ui->lw_song->insertItem(i, QString::fromStdString(currentSong.songName));
    }
}

void MainWindow::playPressed()
{
    current_songName = ui->lw_song->currentItem()->text().toUtf8().constData();


    LinkedList<song>* song_list = myArtistFetcher->artist_list[current_artist]->songs;

    song current_song;
    for(int i=0; i < song_list->getSize(); i++){
        song current = song_list->get(i)->data;
        std::string songName = current.artistName;
            current_song = current;
            if(strcmp(current_songName.c_str(), current.songName.c_str()) == 0){
            break;
        }
    }

    std::string id = std::to_string(current_song.songId);
    std::string path = myRC.getSongPathById(id);

    if(strcmp(path.c_str(), SONG_NOT_FOUND) == 0){
        alert("La cancion no existe");
        return;

    }

    log(path);
    LoadTrack().playMusic(path);
}

void MainWindow::alert(std::string alertMessage)
{
    QMessageBox reply;
    reply.setText(QString::fromStdString(alertMessage));
    reply.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}

