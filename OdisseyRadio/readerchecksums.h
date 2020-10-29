#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"
#include "song.h"


class readerChecksums
{
public:
    std::string path;

    readerChecksums();

    std::string getString(std::string line);

    int getSongById(std::string songId);

    LinkedList<song> getNext(std::string songId);

    LinkedList<song> getPrevious(std::string songId);

    LinkedList<song> getFirst();

    std::string getPrevious();

    std::string getSongPath(std::string songString);

    std::string getSongId(std::string songString);

};


