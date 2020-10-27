#include "readerchecksums.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#define log(x) std::cout<<x<<std::endl;


std::string path = "/home/migue/Desktop/fma_small/checksums";
std::string line;

readerChecksums::readerChecksums()
{

}

std::string readerChecksums::getString(){
    std::ifstream ip(::path);
    log(::path)
    getline(ip,::line,'\n');
    log(::line);
    return ::line;
}







std::string getSongPath();

std::string getSongId();


void readerChecksums::something(){
    log("hola desde aqui")
}




int main(){
    readerChecksums myReader;
    myReader.getString();
}
