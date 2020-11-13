#include "readerchecksums.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include "LinkedList.h"
#include "song.h"
#include <QMessageBox>
#define log(x) std::cout<<x<<std::endl;


std::string path = "/home/migue/Desktop/fma_small/checksums";


readerChecksums::readerChecksums()
{

}

/**
 * @brief readerChecksums::getSongId Takes a line from the file checksums and return the id from that song
 * @param songString Line from checksums
 * @return
 */
std::string readerChecksums::getSongId(std::string songString){
    std::string temp = songString.erase(0,46);
    return temp.erase(6,4);
}


/**
 * @brief readerChecksums::getSongById Gets a song position int the csv with its id
 * @param songId
 * @return  Position in the csv where the song is
 */
int readerChecksums::getSongById(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    int songPos=0;
    int localId = 0;
    int otherId = 0;
    std::stringstream xdd(songId);
    xdd >> otherId;
    if (songId=="000000")
        return 0;
    while (true){
        songPos+=1;
        getline(ip,line,'\n');
        std::string temp = getSongId(line);
        std::stringstream xd(temp);
        xd >> localId;
        if(localId==otherId){
            //log(songPos)
            getline(ip,line,'\n');
            return songPos;
        }
        else if (localId > otherId){
            return -1;
        }
    }
    return songPos;
}


LinkedList<song> readerChecksums::getFirst(){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    for(int i = 0; i < 20; i++)
    {
        song newSong;
        getline(ip,line,'\n');
        myList.addNodo(newSong);
    }
    return myList;
}

LinkedList<song> readerChecksums::getPrevious(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    //std::vector<std::string> myVector(10);
    int reps = getSongById(songId);
    for (int i=0; i<reps-21; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 20; i++)
    {
        song newSong;
        getline(ip,line,'\n');
//        newSong.songId=getSongId(line);
//        newSong.songPath=getSongPath(line);
        myList.addNodo(newSong);
        //myVector[i]=line;
    }

    return myList;
    // Used to return myVector
}

/**
 * @brief readerChecksums::getSongPathById Takes a sogn id and return the path of the song
 * @param id Song id
 * @return Song path
 */
std::string readerChecksums::getSongPathById(std::string id)
{
    std::ifstream ip(::path);
    std::string line;
    int reps = getSongById(id);

    if(reps == -1){return "";}
    for (int i=0; i<reps; i++)
    {
        getline(ip,line,'\n');
    }
    //getline(ip,line,'\n');
    return getSongPath(line);
}


LinkedList<song> readerChecksums::getNext(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    int reps = getSongById(songId);
    for (int i=0; i<reps; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 20; i++)
    {
        song newSong;
        getline(ip,line,'\n');
        myList.addNodo(newSong);
    }

    return myList;
}

/**
 * @brief readerChecksums::getSongPath Takes a line from the checksums file and returns the path of a song
 * @param songString Line from checksums file
 * @return Song path
 */
std::string readerChecksums::getSongPath(std::string songString){
    std::string myPath = "/home/migue/Desktop/fma_small/";
    myPath+=songString.erase(0,42);
    return myPath;
}
