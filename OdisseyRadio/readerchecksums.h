#pragma once
#include <iostream>
#include <string>
#include <vector>


class readerChecksums
{
public:
    std::string path;
    



    readerChecksums();

    std::string getString(std::string line);

    void getIp(std::string songId);

    std::vector<std::string> getNext(std::string songId);

    std::string getPrevious();

    std::string getSongPath(std::string songString);

    std::string getSongId(std::string songString);

};


