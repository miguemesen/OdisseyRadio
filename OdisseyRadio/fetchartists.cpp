#include "fetchartists.h"
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#define log(x) std::cout<<x<<std::endl;
//#include "reader.h"
//#include "readerchecksums.h"

std::string path;
std::string path2;

fetchArtists::fetchArtists()
{

}

bool fetchArtists::exist(std::string artistName, LinkedList<std::string> list)
{
    for (int i=0; i<list.getSize(); i++)
    {
        if (list.get(i)->data==artistName)
            return true;
    }
    return false;
}


LinkedList<std::string> fetchArtists::getArtists()
{
    LinkedList<std::string> myArtists;
    std::ifstream ip1(::path);
    std::ifstream ip2(::path2);
    std::string line1;
    std::string line2;

    for (int i=0; i < 8000; i++)
    {

    }

    return myArtists;
}

int main()
{
    log("hola")
    LinkedList<std::string> myList;
    myList.addNodo("Miguel");
    myList.addNodo("Pedro");
    myList.addNodo("Ericka");
    myList.addNodo("Allan");
    log(myList.getSize())
    fetchArtists myFetcher;
    myFetcher.exist("Pedro",myList);
}

