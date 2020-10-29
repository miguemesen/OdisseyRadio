#pragma once
#include <iostream>
#include <string>
#include "LinkedList.h"
#include <vector>


class reader
{
public:
    std::string songName;
    std::string artistName;
    std::string songLength;
    std::string songGenre;
    std::string line;
    int localId;
    LinkedList<std::string> myList;
    std::vector<std::string> csvColumn;
    std::string path;
    std::string path2;
    reader();
};




