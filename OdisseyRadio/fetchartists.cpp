#include "fetchartists.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#define log(x) std::cout<<x<<std::endl;
#include "reader.h"
#include "readerchecksums.h"

std::string myPath = "/home/migue/Desktop/fma_small/checksums";
reader myReader;
readerChecksums myReaderCh;

fetchArtists::fetchArtists()
{

}

bool fetchArtists::exist(std::string artistName, LinkedList<std::string> list)
{
    for (int i=0; i<list.getSize(); i++)
    {
        if (list.isEmpty())
            return false;
        if (list.get(i)->data==artistName)
            return true;
    }
    return false;
}


LinkedList<std::string> fetchArtists::getArtists()
{
    LinkedList<std::string> myArtists;
    std::ifstream ip1(::myPath);
    std::string line1;
    for (int i=0; i < 8000; i++)
    {
        getline(ip1,line1,'\n');
        std::string tempId = myReaderCh.getSongId(line1);
        stringstream temp(tempId);
        int tempIdInt = 0;
        temp >> tempIdInt;
        myReader.getIp(tempIdInt);
        myReader.fillCsvColumn();
        myReader.fillList();
        myReader.assignSongInfo();
        std::string tempArtist = myReader.artistName;

        if (!exist(tempArtist,myArtists))
        {
            myArtists.addNodo(tempArtist);
        }
    }

    return myArtists;
}

//int main()
//{
//    log("hola")
//    LinkedList<std::string> myList;
//    myList.addNodo("Miguel");
//    myList.addNodo("Pedro");
//    myList.addNodo("Ericka");
//    myList.addNodo("Allan");
//    log(myList.getSize())
//    fetchArtists myFetcher;
//    myFetcher.exist("Pedro",myList);
//}

