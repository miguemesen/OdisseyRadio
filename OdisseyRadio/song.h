#pragma once
#include <iostream>
#include <string>
#include <QListWidgetItem>

using namespace std;

class song : public QListWidgetItem
{
public:
    QString songName;
    QString artistName;
    string songLength;
    string songGenre;
    int songId;
    string songPath;
    song();
};


