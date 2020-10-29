#pragma once
#include <iostream>
#include <string>
#include <QListWidgetItem>

using namespace std;

class song : public QListWidgetItem
{
public:
    QString songName;
    string artistName;
    string songLength;
    string songGenre;
    string songId;
    string songPath;
    song();
};


