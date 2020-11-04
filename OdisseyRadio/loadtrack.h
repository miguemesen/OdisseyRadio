#ifndef LOADTRACK_H
#define LOADTRACK_H

#include <iostream>

#include <QMediaPlayer>

#define default_volume 100

class LoadTrack
{
public:
    LoadTrack();

    static QMediaPlayer* player;

    static void loadMusic(std::string& path)
    {
        player->setMedia(QUrl::fromLocalFile(QString::fromStdString(path)));
        player->setVolume(default_volume);
    }


    static void playMusic()
    {
        player->play();
    }

    static void pauseMusic(){
        player->pause();

    }
};

#endif // LOADTRACK_H
