#include "readerchecksums.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include "LinkedList.h"
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
    std::cout<<"this is otherId: "<<otherId<<std::endl;
    if (songId=="000000")
        return 0;
    while (true){
        songPos+=1;
        log(songPos)
        getline(ip,line,'\n');
        std::string temp = getSongId(line);
        std::stringstream xd(temp);
        xd >> localId;
        log(localId)
        if(localId==otherId){
            log("logging from if")
            log(line);
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

std::vector<std::string> readerChecksums::getPrevious(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    std::vector<std::string> myVector(5);
    int reps = getSongById(songId);
    std::cout<<"esto es reps: "<<reps<<std::endl;
    for (int i=0; i<reps-6; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 5; i++)
    {
        getline(ip,line,'\n');
        myVector[i]=line;
    }

    return myVector;
}


// Gets next 5 lines and returns them in a vector
std::vector<std::string> readerChecksums::getNext(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    std::vector<std::string> myVector(5);
    int reps = getSongById(songId);
    log(line);
    for (int i=0; i<reps; i++)
    {
        getline(ip,line,'\n');
    }
    for(int i = 0; i < 5; i++)
    {
        getline(ip,line,'\n');
        myVector[i]=line;
    }

    return myVector;
}

std::string readerChecksums::getSongPath(std::string songString){
    return songString.erase(0,42);
}





//int main(){
//    readerChecksums myReader;
//    std::vector<std::string> xd = myReader.getNext("000182");
//    log(xd[0]);
//    log(xd[1]);
//    log(xd[2]);
//    log(xd[3]);
//    log(xd[4]);

//}
