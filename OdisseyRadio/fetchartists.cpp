#include "fetchartists.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#define log(x) std::cout<<x<<std::endl;
#include "csvparse.h"
#include "artist.h"
#include "song.h"

std::string myPath = "/home/migue/Desktop/fma_metadata/raw_artists.csv";

fetchArtists::fetchArtists()
{

}

void fetchArtists::getArtists(int position)
{
    int artistCount = 0;
    LinkedList<artist>* artists = new LinkedList<artist>;
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);
    std::string temp="";

    while (artist_list.size()<11)
    {
        if (temp=="")
        {
            song *mySong = new song();


            mySong->artistName = parsedCsv[position][5];

            mySong->songLength = parsedCsv[position][21];

            mySong->songId = stoi(parsedCsv[position][0]);
            printf("Esta es el id de las canciones,  %d \n", mySong->songId);

            std::string artistName2 = parsedCsv[position][5];
            mySong->songName = parsedCsv[position][37];

            artist *myArtist = new artist();
            myArtist->artistName = mySong->artistName;
            //log(*myArtist->artistName)
            myArtist->songs->addNodo(*mySong);
            artists->addNodo(*myArtist);
            artist_list[artistName2] = myArtist;
            artistCount+=1;
            position+=1;


            temp= mySong->artistName;
        }

        while (temp==parsedCsv[position][5])
        {
            song *mySong = new song;
            mySong->artistName = parsedCsv[position][5];
            mySong->songName = parsedCsv[position][37];
            //artists->get(artistCount-1)->data.songs->addNodo(*mySong);
            mySong->songId = stoi(parsedCsv[position][0]);

            //------------------------------------------------------

            artist_list[temp]->songs->addNodo(*mySong);

            //------------------------------------------------------



            printf("Esta es el id de las canciones,  %d \n", mySong->songId);


            temp= mySong->artistName;
            position+=1;
//            std::string utf8_text = mySong->songName.toUtf8().constData();
//            log(utf8_text)
        }
        //log(temp)
        temp="";
    }
}



