#pragma once
#include <string>
#include "LinkedList.h"
#include "artist.h"
#include "unordered_map"

class fetchArtists
{
public:
    int finalPosition;

    int firstPosition;

    void getArtists(int position);

    void getPreviousArtist(int position);

    void getNextArtists(int position);

    std::map<std::string, artist*> artist_list;

    bool exist(std::string artistName, LinkedList<std::string> list);

    fetchArtists();


};


