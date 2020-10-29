#pragma once
#include <string>
#include "LinkedList.h"

class fetchArtists
{
public:

    LinkedList<std::string> getArtists();

    //std::string path;

    bool exist(std::string artistName, LinkedList<std::string> list);

    fetchArtists();
};


