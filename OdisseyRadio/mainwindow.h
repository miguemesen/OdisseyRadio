#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include "QListWidgetItem"
#include <QMediaPlayer>
#include "song.h"
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QMediaPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    std::string current_artist;
    std::string current_songName;


    ~MainWindow();

private slots:
    void pageManager();
    void artistManager();
    void artistPressed(QListWidgetItem* myItem);
    void alert(std::string alertMessage);
    void nextArtistPage();
    void previousArtistPage();

    void onSongClicked();
    void on_btn_play_clicked();
    void on_btn_pause_clicked();
    void on_songSlider_valueChanged(int value);
    void on_btn_allsongs_clicked();
    void on_btn_byartist_clicked();

    void nextPage();
    void previousPage();

    void addToAllMap(std::map<std::string,song*> myMap);
    std::vector<std::string> addToSongVector(std::map<std::string,song*> myMap);

    void on_btn_stop_clicked();

    void on_btn_next_clicked();

    void on_btn_previous_clicked();

    void on_checkBox_paging_clicked();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *myMediaPlayer;

};
#endif // MAINWINDOW_H
