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


void readerChecksums::getIp(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    int localId = 0;
    int otherId = 0;
    std::stringstream xdd(songId);
    xdd >> otherId;
    log(otherId)
    while (true){
        getline(ip,line,'\n');
        std::string temp = getSongId(line);
        std::stringstream xd(temp);
        xd >> localId;
        log(localId)
        if(localId==otherId){
            log("logging from if")
            log(line)
            getline(ip,line,'\n');
            break;
        }
        else if (localId > otherId){
            log("No existe esta pieza")
            break;
        }
//        else{

//            getline(ip,line,'\n');
//            log("log desde else");
//            std::cout<<"line desde el else: "<<line<<std::endl;
//        }
    }
}


// Gets next 5 lines and returns them in a vector
std::vector<std::string> readerChecksums::getNext(std::string songId){
    std::ifstream ip(::path);
    std::string line;
    std::vector<std::string> myVector(5);

    while (true)
    {

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





int main(){
    readerChecksums myReader;
    myReader.getIp("000003");
}
