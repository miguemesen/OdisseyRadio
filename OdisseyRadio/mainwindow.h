#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QListWidgetItem"
#include "artist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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
    void playPressed();
    void pausePressed();
    void alert(std::string alertMessage);
    void nextArtistPage();
    void previousArtistPage();
    void songPressed();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
