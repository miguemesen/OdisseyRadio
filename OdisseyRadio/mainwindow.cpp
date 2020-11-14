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

fetchArtists* myArtistFetcher = new fetchArtists();
fetchArtists* nextArtistFetcher = new fetchArtists();
fetchArtists* previousArtistFetcher = new fetchArtists();

std::vector<std::string> previousSongNames;
std::vector<std::string> currentSongNames;
std::vector<std::string> nextSongNames;

int songPosition;
int finalPositionX;
int firstPosition;

bool allButton;
bool artistButton;


std::map<std::string, song*> allSongsMap;


/**
 * @brief MainWindow::MainWindow Starts app and runs it in an event
 * @param parent
 * @author miguemesen
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myMediaPlayer = new QMediaPlayer(this);

    connect(ui->lw_artists,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(artistPressed(QListWidgetItem*)));

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

    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));

}

/**
 * @brief MainWindow::onSongClicked If the clicked element is part of the existing songs on the computer it loads the song and prepares it to be played
 * @author miguemesen
 */
void MainWindow::onSongClicked()
{
    if(allButton)
    {
        ui->label_SN_text->setText(QString::fromStdString(allSongsMap[ui->lw_song->currentItem()->text().toUtf8().constData()]->songName));
        ui->label_AN_text->setText(QString::fromStdString(allSongsMap[ui->lw_song->currentItem()->text().toUtf8().constData()]->artistName));
        ui->label_SID->setText(QString::number(allSongsMap[ui->lw_song->currentItem()->text().toUtf8().constData()]->songId));
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

    ui->label_SN_text->setText(QString::fromStdString(current_song.songName));
    ui->label_AN_text->setText(QString::fromStdString(current_song.artistName));
    ui->label_SID->setText(QString::number(current_song.songId));

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

/**
 * @brief MainWindow::pageManager Controls in which direction the paging is going
 * @author gabo1305
 */
void MainWindow::pageManager()
{
    if(ui->lw_song->verticalScrollBar()->value()>=48 && allButton)
    {
        ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
        nextPage();
        ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
    }

    if(ui->lw_song->verticalScrollBar()->value()<=2 && allButton)
    {
        ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
        previousPage();
        ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
    }
}

/**
 * @brief MainWindow::previousPage Gets the previous 20 songs from the csv and deletes the songs that were in the next page
 * @author miguemesen
 */
void MainWindow::previousPage()
{
    if(ui->checkBox_paging->isChecked())
    {
        ui->lw_song->verticalScrollBar()->setSliderPosition(18);
        // Delete next songs
        for(int i=0; i<20; i++)
        {
            song* temp = allSongsMap[ui->lw_song->item(40)->text().toUtf8().constData()];
            ui->lw_song->takeItem(40);
            allSongsMap.erase(nextSongNames[i]);
            delete temp;
        }

        nextSongNames.clear();
        nextSongNames=currentSongNames;
        currentSongNames.clear();
        currentSongNames = previousSongNames;

    }
        previousSongNames.clear();

        mySongFetcher->fetchSongs(songPosition-80);
        previousSongNames = addToSongVector(mySongFetcher->song_list);
        addToAllMap(mySongFetcher->song_list);
        mySongFetcher->song_list.clear();
        songPosition-=20;
    //}

    int index2 = 0;
    for (int i=0; i<20; i++)
    {
        ui->lw_song->insertItem(index2,QString::fromStdString(previousSongNames[i]));
        index2++;
    }
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
}

/**
 * @brief MainWindow::nextPage Gets the next 20 songs from the csv and deletes the songs that were in the previous page
 * @author miguemesen
 */
void MainWindow::nextPage()
{
    if(ui->checkBox_paging->isChecked())
    {
        ui->lw_song->verticalScrollBar()->setSliderPosition(18);

        // Delete previous songs
        for(int i=0; i<20; i++)
        {
            song* temp = allSongsMap[ui->lw_song->item(0)->text().toUtf8().constData()];
            ui->lw_song->takeItem(0);
            allSongsMap.erase(previousSongNames[i]);
            delete temp;
        }

        previousSongNames.clear();
        previousSongNames=currentSongNames;
        currentSongNames.clear();
        currentSongNames = nextSongNames;
    }
        nextSongNames.clear();

        mySongFetcher->fetchSongs(songPosition);
        nextSongNames = addToSongVector(mySongFetcher->song_list);
        addToAllMap(mySongFetcher->song_list);
        mySongFetcher->song_list.clear();
        songPosition+=20;
    //}

    int index2 = 40;
    for (int i=0; i<20; i++)
    {
        ui->lw_song->insertItem(index2,QString::fromStdString(nextSongNames[i]));
        index2++;
    }
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
}

/**
 * @brief MainWindow::previousArtistPage Gets the previous 5 artists and inserts them into the artist list widget
 * @author gabo1305
 */
void MainWindow::previousArtistPage()
{
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

/**
 * @brief MainWindow::nextArtistPage Gets the next 5 artists and inserts them into the artist list widget
 * @author gabo1305
 */
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

/**
 * @brief MainWindow::artistManager Initializes or resets the search through artist option
 * @author gabo1305
 */
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

/**
 * @brief MainWindow::artistPressed Displays on the song list widget all the songs from the artist.
 * @param myItem Song from the list widget
 * @author miguemesen
 */
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

/**
 * @brief MainWindow::alert Throws an alert
 * @param alertMessage Message wished to display
 * @author gabo1305
 */
void MainWindow::alert(std::string alertMessage)
{
    QMessageBox reply;
    reply.setText(QString::fromStdString(alertMessage));
    reply.exec();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_btn_play_clicked Action when play button is clicked
 * @author gabo1305
 */
void MainWindow::on_btn_play_clicked()
{
    myMediaPlayer->play();
}

/**
 * @brief MainWindow::on_btn_pause_clicked Action when pause button is clicked
 * @author gabo1305
 */
void MainWindow::on_btn_pause_clicked()
{
    myMediaPlayer->pause();
}

/**
 * @brief MainWindow::on_songSlider_valueChanged Actions that interact with the song slider
 * @param value new position of the song
 * @author gabo1305
 */
void MainWindow::on_songSlider_valueChanged(int value)
{
    myMediaPlayer->setPosition(value);
    //ui->songSlider->setValue(value);
}

/**
 * @brief MainWindow::on_btn_allsongs_clicked Action when all songs button is clicked. Loads three pages filled with songs into the song list widget
 * @author miguemesen
 */
void MainWindow::on_btn_allsongs_clicked()
{
    artistButton = false;
    allButton = true;
    ui->lw_artists->clear();
    ui->lw_song->clear();
    previousSongNames.clear();
    currentSongNames.clear();
    nextSongNames.clear();
    songPosition=1584;

    mySongFetcher->fetchSongs(songPosition);
    previousSongNames = addToSongVector(mySongFetcher->song_list);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=20;

    mySongFetcher->fetchSongs(songPosition);
    currentSongNames = addToSongVector(mySongFetcher->song_list);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=20;

    mySongFetcher->fetchSongs(songPosition);
    nextSongNames = addToSongVector(mySongFetcher->song_list);
    addToAllMap(mySongFetcher->song_list);
    mySongFetcher->song_list.clear();
    songPosition+=20;

    int index = 0;
    for (int i=0; i<20; i++)
    {
        ui->lw_song->insertItem(index,QString::fromStdString(previousSongNames[i]));
        index++;
    }

    for (int i=0; i<20; i++)
    {
        ui->lw_song->insertItem(index,QString::fromStdString(currentSongNames[i]));
        index++;
    }

    for (int i=0; i<20; i++)
    {
        ui->lw_song->insertItem(index,QString::fromStdString(nextSongNames[i]));
        index++;
    }

//    int index = 0;
//    for(std::unordered_map<std::string,song*>::iterator it=allSongsMap.begin(); it != allSongsMap.end(); it++)
//    {
//        ui->lw_song->insertItem(index,QString::fromStdString(it->second->songName));
//        index++;
//    }
}

/**
 * @brief MainWindow::addToAllMap Adds songs from one map to another
 * @param myMap Map from which is desired to extract songs
 * @author miguemesen
 */
void MainWindow::addToAllMap(std::map<std::string,song*> myMap)
{
    for(std::map<std::string,song*>::iterator it=myMap.begin(); it != myMap.end(); it++)
    {
        allSongsMap[it->second->songName] = it->second;
    }
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
}

/**
 * @brief MainWindow::addToSongVector Fills a vector with the names of songs that come from a map
 * @param myMap Map from which is desired to get song names
 * @return
 */
std::vector<std::string> MainWindow::addToSongVector(std::map<std::string,song*> myMap)
{
    std::vector<std::string> myVector;
    for(std::map<std::string,song*>::iterator it=myMap.begin(); it != myMap.end(); it++)
    {
        myVector.push_back(it->second->songName);
    }
    ui->label_2->setText(QString::number( s_AllocationMetrics.CurrentUsage()));
    return myVector;
}

/**
 * @brief MainWindow::on_btn_byartist_clicked Calls the artist manager
 * @author gabo1305
 */
void MainWindow::on_btn_byartist_clicked()
{
    allButton=false;
    artistButton=true;
    artistManager();
}

/**
 * @brief MainWindow::on_btn_stop_clicked
 */
void MainWindow::on_btn_stop_clicked()
{
    myMediaPlayer->stop();
}

/**
 * @brief MainWindow::on_btn_next_clicked
 */
void MainWindow::on_btn_next_clicked()
{
    if(artistButton)
    {
        nextArtistPage();
    }
}

/**
 * @brief MainWindow::on_btn_previous_clicked
 */
void MainWindow::on_btn_previous_clicked()
{
    if(artistButton)
    {
        previousArtistPage();
    }
}
