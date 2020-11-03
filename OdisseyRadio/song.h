#pragma once
#include <iostream>
#include <string>
#include <QListWidgetItem>

using namespace std;

class song : public QListWidgetItem
{
public:
    string songName;
    string artistName;
    string songLength;
    string songGenre;
    int songId;
    string songPath;
    song();
};


