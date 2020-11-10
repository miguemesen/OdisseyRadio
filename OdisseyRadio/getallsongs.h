#pragma once
#include "csvparse.h"
#include "sstream"
#include <bits/stdc++.h>
#include <iostream>
#include "unordered_map"
#include "song.h"
#include "readerchecksums.h"


class getallsongs
{
public:

    readerChecksums myRCsums;

    std::map<std::string, song*> song_list;

    void fetchPreviousSongs(int position);

    void fetchSongs(int position);

    getallsongs();
};


