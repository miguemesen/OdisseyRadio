#pragma once
#include <string>
#include "LinkedList.h"

class fetchArtists
{
public:

    LinkedList<std::string> getArtists();

    std::string path;
    std::string path2;

    bool exist(std::string artistName, LinkedList<std::string> list);

    fetchArtists();
};


