#include "readerchecksums.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include "LinkedList.h"
#include "song.h"
#define log(x) std::cout<<x<<std::endl;


std::string path = "/home/migue/Desktop/fma_small/checksums";


readerChecksums::readerChecksums()
{

}

std::string readerChecksums::getSongId(std::string songString){
    std::string temp = songString.erase(0,46);
    return temp.erase(6,4);
}


// Gets a song position with its id
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
            log("No existe esta pieza")
            break;
        }
    }
    return songPos;
}

LinkedList<song> readerChecksums::getFirst(){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    //std::vector<std::string> myVector(10);
    for(int i = 0; i < 12; i++)
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

LinkedList<song> readerChecksums::getPrevious(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    //std::vector<std::string> myVector(10);
    int reps = getSongById(songId);
    for (int i=0; i<reps-13; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 12; i++)
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


std::string readerChecksums::getSongPathById(std::string id)
{
    std::ifstream ip(::path);
    std::string line;
    int reps = getSongById(id);
    for (int i=0; i<reps; i++)
    {
        getline(ip,line,'\n');
    }
    //getline(ip,line,'\n');
    return getSongPath(line);
}


// Gets next 5 lines and returns them in a vector
LinkedList<song> readerChecksums::getNext(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    LinkedList<song> myList;
    //std::vector<std::string> myVector(10);
    int reps = getSongById(songId);
    for (int i=0; i<reps; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 12; i++)
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

std::string readerChecksums::getSongPath(std::string songString){
    std::string myPath = "/home/migue/Desktop/fma_small/";
    myPath+=songString.erase(0,42);
    return myPath;
}





//int main(){
//    readerChecksums myReader;
//    LinkedList<std::string> newList = myReader.getNext("000005");
//    for (int i = 0; i<10; i++)
//    {
//        log(newList.get(i)->data)
//    }
//    std::cout<<"this is song path: "<<myReader.getSongPath(newList.get(3)->data)<<std::endl;
//    std::cout<<"this is song Id: "<<myReader.getSongId(newList.get(3)->data)<<std::endl;
//}
