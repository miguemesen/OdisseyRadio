#pragma once
#include "LinkedList.h"
#include "song.h"
#include "QListWidgetItem"

class artist : public QListWidgetItem
{
public:
    LinkedList<song> *songs;
    string artistName;
    artist();
};


