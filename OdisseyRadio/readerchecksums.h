#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"
//#include "song.h"


class readerChecksums
{
public:
    std::string path;

    readerChecksums();

    std::string getString(std::string line);

    int getSongById(std::string songId);

    LinkedList<std::string> getNext(std::string songId);

    LinkedList<std::string> getPrevious(std::string songId);

    LinkedList<std::string> getFirst();

    std::string getPrevious();

    std::string getSongPath(std::string songString);

    std::string getSongId(std::string songString);

};


