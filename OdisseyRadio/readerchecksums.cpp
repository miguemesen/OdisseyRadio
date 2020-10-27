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


std::string readerChecksums::getString(std::string line){
    std::ifstream ip(::path);
    getline(ip,line,'\n');
    getline(ip,line,'\n');
    return line;
}

// Gets next 5 lines and returns them in a vector
std::vector<std::string> readerChecksums::getNext(){
    std::ifstream ip(::path);
    std::string line;
    std::vector<std::string> myVector(5);
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

std::string readerChecksums::getSongId(std::string songString){
    std::string temp = songString.erase(0,46);
    return temp.erase(6,4);
}



int main(){
    readerChecksums myReader;
    myReader.getSongId("6976e70271234351250ada3fc49c5afd69ba9864  000/000002.mp3");
}
