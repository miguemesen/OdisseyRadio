#include "fetchartists.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#define log(x) std::cout<<x<<std::endl;
#include "csvparse.h"
#include "artist.h"
#include "song.h"

std::string myPath = "/home/migue/Desktop/fma_metadata/raw_artists.csv";
//int finalPosition;
//int firstPosition=1592;

fetchArtists::fetchArtists()
{

}

void fetchArtists::getPreviousArtist(int position)
{
    finalPosition = position;
    int newPosition = position-1;
        std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
        std::vector<std::vector<std::string>> parsedCsv;
        csvparse myParse;
        parsedCsv = myParse.readCSV(ip);
        std::string temp="";
        while (artist_list.size()!=5)
        {
            if (temp=="")
            {
                song *mySong = new song();
                mySong->artistName = parsedCsv[newPosition][5];
                mySong->songLength = parsedCsv[newPosition][21];
                mySong->songId = stoi(parsedCsv[newPosition][0]);
                std::string artistName2 = parsedCsv[newPosition][5];
                mySong->songName = parsedCsv[newPosition][37];
                artist *myArtist = new artist();
                myArtist->artistName = mySong->artistName;
                myArtist->songs->addNodo(*mySong);
                artist_list[artistName2] = myArtist;
                newPosition-=1;
                temp= mySong->artistName;
            }
            while (temp==parsedCsv[newPosition][5])
            {
                song *mySong = new song;
                mySong->artistName = parsedCsv[newPosition][5];
                mySong->songName = parsedCsv[newPosition][37];
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

void fetchArtists::getArtists(int position)
{
//    int artistCount = 0;
//    LinkedList<artist>* artists = new LinkedList<artist>;
    firstPosition=position;
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);
    std::string temp="";

    while (artist_list.size()!=5)
    {
        if (temp=="")
        {
            song *mySong = new song();

            mySong->artistName = parsedCsv[position][5];

            mySong->songLength = parsedCsv[position][21];

            mySong->songId = stoi(parsedCsv[position][0]);

            std::string artistName2 = parsedCsv[position][5];
            mySong->songName = parsedCsv[position][37];

            artist *myArtist = new artist();
            myArtist->artistName = mySong->artistName;
            //log(*myArtist->artistName)
            myArtist->songs->addNodo(*mySong);
            //artists->addNodo(*myArtist);
            artist_list[artistName2] = myArtist;
            //artistCount+=1;
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
            temp= mySong->artistName;
            position+=1;
        }
        temp="";
        finalPosition=position;
    }
}

void fetchArtists::getNextArtists(int position)
{
    int artistCount = 0;
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);
    std::string temp="";

    while (artist_list.size()!=10)
    {

        if (temp=="" && artistCount<10)
        {
            temp=parsedCsv[position][5];
            artistCount+=1;
            position+=1;
        }

        while(temp==parsedCsv[position][5] && artistCount<=10)
        {
            temp= parsedCsv[position][5];
            position+=1;
        }

        if (temp=="" && artistCount>=10)
        {
            song *mySong = new song();

            mySong->artistName = parsedCsv[position][5];

            mySong->songLength = parsedCsv[position][21];

            mySong->songId = stoi(parsedCsv[position][0]);

            std::string artistName2 = parsedCsv[position][5];
            mySong->songName = parsedCsv[position][37];

            artist *myArtist = new artist();
            myArtist->artistName = mySong->artistName;
            //log(*myArtist->artistName)
            myArtist->songs->addNodo(*mySong);
            //artists->addNodo(*myArtist);
            artist_list[artistName2] = myArtist;
            artistCount+=1;
            position+=1;
            temp= mySong->artistName;
        }
        while (temp==parsedCsv[position][5] && artistCount>=10)
        {
            song *mySong = new song;
            mySong->artistName = parsedCsv[position][5];
            mySong->songName = parsedCsv[position][37];
            //artists->get(artistCount-1)->data.songs->addNodo(*mySong);
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



