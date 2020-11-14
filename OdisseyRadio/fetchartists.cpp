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

/**
 * @brief fetchArtists::getPreviousArtist Gets the previous five artist with their respective songs from a positon in the csv
 * @param position Position inside the csv
 */
void fetchArtists::getPreviousArtist(int position)
{
    finalPosition = position;
    int newPosition = position-1;
        std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
        std::vector<std::vector<std::string>> parsedCsv;
//        csvparse myParse;
//        parsedCsv = myParse.readCSV(ip);
        parsedCsv = csvparse::myReadCsv();
        std::string temp="";
        while (artist_list.size()!=5)
        {
            if (temp=="")
            {
                song *mySong = new song();
                mySong->artistName = parsedCsv[newPosition][1];
                //mySong->songLength = parsedCsv[newPosition][21];
                mySong->songId = stoi(parsedCsv[newPosition][0]);
                std::string artistName2 = parsedCsv[newPosition][1];
                mySong->songName = parsedCsv[newPosition][2];
                artist *myArtist = new artist();
                myArtist->artistName = mySong->artistName;
                myArtist->songs->addNodo(*mySong);
                artist_list[artistName2] = myArtist;
                newPosition-=1;
                temp= mySong->artistName;
            }
            while (temp==parsedCsv[newPosition][1])
            {
                song *mySong = new song;
                mySong->artistName = parsedCsv[newPosition][1];
                mySong->songName = parsedCsv[newPosition][2];
                mySong->songId = stoi(parsedCsv[newPosition][0]);
                //------------------------------------------------------

                artist_list[temp]->songs->addNodo(*mySong);

                //------------------------------------------------------
                temp= mySong->artistName;
                newPosition-=1;
            }
            temp="";
            firstPosition = newPosition+1;
        }
}

/**
 * @brief fetchArtists::getArtists Gets the next five artist with their respective songs from a positon in the csv
 * @param position Position inside the csv
 */
void fetchArtists::getArtists(int position)
{
    firstPosition=position;
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
    std::vector<std::vector<std::string>> parsedCsv;
//    csvparse myParse;
//    parsedCsv = myParse.readCSV(ip);
    parsedCsv = csvparse::myReadCsv();
    std::string temp="";

    while (artist_list.size()!=5)
    {
        if (temp=="")
        {
            song *mySong = new song();

            mySong->artistName = parsedCsv[position][1];

            //mySong->songLength = parsedCsv[position][21];

            mySong->songId = stoi(parsedCsv[position][0]);

            std::string artistName2 = parsedCsv[position][1];
            mySong->songName = parsedCsv[position][2];

            artist *myArtist = new artist();
            myArtist->artistName = mySong->artistName;
            myArtist->songs->addNodo(*mySong);
            artist_list[artistName2] = myArtist;
            position+=1;
            temp= mySong->artistName;
        }
        while (temp==parsedCsv[position][1])
        {
            song *mySong = new song;
            mySong->artistName = parsedCsv[position][1];
            mySong->songName = parsedCsv[position][2];
            mySong->songId = stoi(parsedCsv[position][0]);

            //------------------------------------------------------

            artist_list[temp]->songs->addNodo(*mySong);

            //------------------------------------------------------
            temp= mySong->artistName;
            position+=1;
        }
        temp="";
        finalPosition=position;
    }
}




