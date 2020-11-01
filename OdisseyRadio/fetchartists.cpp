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


LinkedList<artist> fetchArtists::getArtists(int position)
{
    int artistCount = 0;
    LinkedList<artist> artists;
    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
    std::vector<std::vector<std::string>> parsedCsv;
    csvparse myParse;
    parsedCsv = myParse.readCSV(ip);
    std::string temp="";

    while (artistCount<11)
    {
        if (temp=="")
        {
            song *mySong = new song();
            mySong->artistName = parsedCsv[position][5];
            QString qstr = QString::fromStdString(parsedCsv[position][37]);
            mySong->songName = qstr;
            artist *myArtist = new artist();
            myArtist->artistName = &mySong->artistName;
            //log(*myArtist->artistName)
            myArtist->songs->addNodo(*mySong);
            artists.addNodo(*myArtist);
            artistCount+=1;
            position+=1;
            temp=mySong->artistName;
//            std::string utf8_text = mySong->songName.toUtf8().constData();
//            log(utf8_text)
        }

        while (temp==parsedCsv[position][5])
        {
            song *mySong = new song;
            mySong->artistName = parsedCsv[position][5];
            QString qstr = QString::fromStdString(parsedCsv[position][37]);
            mySong->songName = qstr;
            artists.get(artistCount-1)->data.songs->addNodo(*mySong);
            temp=mySong->artistName;
            position+=1;
//            std::string utf8_text = mySong->songName.toUtf8().constData();
//            log(utf8_text)
        }
        //log(temp)
        temp="";
    }
    return artists;
}

//int main()
//{
//    std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks2.csv");
//    std::vector<std::vector<std::string>> parsedCsv;
//    csvparse myParse;
//    parsedCsv = myParse.readCSV(ip);
//    log(parsedCsv[1592][5])
//}


