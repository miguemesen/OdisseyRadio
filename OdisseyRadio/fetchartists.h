#pragma once
#include <string>
#include "LinkedList.h"
#include "artist.h"
#include "unordered_map"

class fetchArtists
{
public:


    void getArtists(int position);


    std::map<std::string, artist*> artist_list;



    //std::string path;

    bool exist(std::string artistName, LinkedList<std::string> list);

    fetchArtists();


};


