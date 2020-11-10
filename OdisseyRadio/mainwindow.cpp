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
#include <QMediaPlayer>
#include "memoryusage.h"
#include "getallsongs.h"

#define log(x) std::cout<<x<<std::endl;

#define default_volume 100
#define SONG_NOT_FOUND ""
#define CURRENT_SONG_NAME_NOT_ASSIGNED ""

readerChecksums myRC;

getallsongs* mySongFetcher = new getallsongs();
getallsongs* nextSongFetcher = new getallsongs();
getallsongs* previousSongFetcher = new getallsongs();

fetchArtists* myArtistFetcher = new fetchArtists();
fetchArtists* nextArtistFetcher = new fetchArtists();
fetchArtists* previousArtistFetcher = new fetchArtists();

int songPosition;
int finalPositionX;
int firstPosition;

bool allButton;
bool artistButton;

std::map<std::string, song*> previousPage;
std::map<std::string, song*> nextPage;
std::map<std::string, song*> currentPage;

std::map<std::string, song*> allSongsMap;


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

    myMediaPlayer = new QMediaPlayer(this);

    connect(ui->lw_artists,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(artistPressed(QListWidgetItem*)));

    connect(ui->btn_next,SIGNAL(clicked()),this,SLOT(nextArtistPage()));

    connect(ui->btn_previous,SIGNAL(clicked()),this,SLOT(previousArtistPage()));

    connect(myMediaPlayer,&QMediaPlayer::positionChanged,[&](qint64 pos){
        ui->songSlider->setValue(pos);
    });

    connect(myMediaPlayer,&QMediaPlayer::durationChanged, [&](qint64 dur){
        ui->songSlider->setMaximum(dur);
    });


    QListWidget* myListW = ui->lw_song;
    connect(myListW,&QListWidget::itemClicked,[&]{onSongClicked();});

    QScrollBar* myScroll2 = ui->lw_song->verticalScrollBar();
    connect(myScroll2,&QScrollBar::valueChanged,[&]{pageManager();});



}


void MainWindow::onSongClicked()
{
    if(allButton)
    {
        if(strcmp(allSongsMap[ui->lw_song->currentItem()->text().toUtf8().constData()]->songPath.c_str(), SONG_NOT_FOUND) == 0)
        {
            alert("La cancion no existe");
            return;
        }
        myMediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(allSongsMap[ui->lw_song->currentItem()->text().toUtf8().constData()]->songPath)));
        myMediaPlayer->setVolume(default_volume);
        return;
    }

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
    myMediaPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(path)));
    myMediaPlayer->setVolume(default_volume);
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
}

void MainWindow::pageManager()
{
//    if(ui->lw_song->verticalScrollBar()->value()==1)
//    {
//        nextSongs();
//        //int index = 0;
//        for(std::map<std::string,song*>::iterator it=currentPage.begin(); it != currentPage.end(); it++)
//        {
//            ui->lw_song->insertItem(myIndex,QString::fromStdString(it->second->songName));
//            myIndex++;
//        }
//    }

}

void MainWindow::previousArtistPage()
{
    //PrintMemoryUsage();
    ui->lw_artists->clear();
    previousArtistFetcher->artist_list.clear();
    previousArtistFetcher->getPreviousArtist(firstPosition);
    myArtistFetcher->artist_list.clear();
    myArtistFetcher->artist_list = previousArtistFetcher->artist_list;
    int index = 0;
    for(std::map<std::string,artist*>::iterator it= myArtistFetcher->artist_list.begin(); it != myArtistFetcher->artist_list.end(); it++)
    {
        ui->lw_artists->insertItem(index, QString::fromStdString(it->second->artistName));
        index++;
    }
    firstPosition = previousArtistFetcher->firstPosition;
    finalPositionX = previousArtistFetcher->finalPosition;
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));}

void MainWindow::nextArtistPage()
{
    ui->lw_artists->clear();
    nextArtistFetcher->artist_list.clear();
    nextArtistFetcher->getArtists(finalPositionX);
    myArtistFetcher->artist_list.clear();
    myArtistFetcher->artist_list = nextArtistFetcher->artist_list;
    //myArtistFetcher->finalPosition = otherArtistFetcher->finalPosition;
    int index = 0;
    for(std::map<std::string,artist*>::iterator it= myArtistFetcher->artist_list.begin(); it != myArtistFetcher->artist_list.end(); it++)
    {
        ui->lw_artists->insertItem(index, QString::fromStdString(it->second->artistName));
        index++;
    }
    firstPosition = nextArtistFetcher->firstPosition;
    finalPositionX = nextArtistFetcher->finalPosition;
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
}

void MainWindow::artistManager()
{
    ui->lw_artists->clear();
    ui->lw_song->clear();
    myArtistFetcher->getArtists(1584);
    int index = 0;
    for(std::map<std::string,artist*>::iterator it= myArtistFetcher->artist_list.begin(); it != myArtistFetcher->artist_list.end(); it++)
    {
        ui->lw_artists->insertItem(index, QString::fromStdString(it->second->artistName));
        index++;
    }
    //position=myArtistFetcher->finalPosition;
    firstPosition = myArtistFetcher->firstPosition;
    finalPositionX = myArtistFetcher->finalPosition;
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
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
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
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

void MainWindow::on_btn_play_clicked()
{
    myMediaPlayer->play();
}

void MainWindow::on_btn_pause_clicked()
{
    myMediaPlayer->pause();
}

void MainWindow::on_songSlider_valueChanged(int value)
{
    myMediaPlayer->setPosition(value);
    //ui->songSlider->setValue(value);
}

void MainWindow::on_btn_allsongs_clicked()
{
    artistButton = false;
    allButton = true;
    ui->lw_artists->clear();
    ui->lw_song->clear();
    songPosition=1584;

    mySongFetcher->fetchSongs(songPosition);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=12;
    mySongFetcher->fetchSongs(songPosition);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=12;
    mySongFetcher->fetchSongs(songPosition);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=12;

    int index = 0;
    for(std::map<std::string,song*>::iterator it=allSongsMap.begin(); it != allSongsMap.end(); it++)
    {
        ui->lw_song->insertItem(index,QString::fromStdString(it->second->songName));
        index++;
    }
    log(index);
}

//_____________________________________________________________________________________________________________

void MainWindow::addToAllMap(std::map<std::string,song*> myMap)
{
    for(std::map<std::string,song*>::iterator it=myMap.begin(); it != myMap.end(); it++)
    {
        allSongsMap[it->second->songName] = it->second;
    }
}

//_____________________________________________________________________________________________________________

void MainWindow::previousSongs()
{
    nextPage.clear();
    nextPage = currentPage;
    currentPage.clear();
    currentPage = previousPage;
    previousPage.clear();
    previousSongFetcher->fetchPreviousSongs(songPosition);
    previousPage = previousSongFetcher->song_list;
    songPosition-=13;
}

void MainWindow::nextSongs()
{
    previousPage.clear();
    previousPage = currentPage;
    currentPage.clear();
    currentPage = nextPage;
    nextPage.clear();
    nextSongFetcher->song_list.clear();
    nextSongFetcher->fetchSongs(songPosition);
    nextPage = nextSongFetcher->song_list;
    songPosition+=13;
}

void MainWindow::on_btn_byartist_clicked()
{
    allButton=false;
    artistButton=true;
    artistManager();
}
