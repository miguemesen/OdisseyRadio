#pragma once
#include "csvparse.h"
#include "sstream"
#include <bits/stdc++.h>
#include <iostream>
#include "unordered_map"
#include "song.h"


class getallsongs
{
public:

    std::map<int, song*> song_list;

    void fetchSongs(int position);

    getallsongs();
};


