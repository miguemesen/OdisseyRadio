#pragma once
#include <string>
#include "LinkedList.h"
#include "artist.h"

class fetchArtists
{
public:

    LinkedList<artist> getArtists(int position);

    //std::string path;

    bool exist(std::string artistName, LinkedList<std::string> list);

    fetchArtists();
};


