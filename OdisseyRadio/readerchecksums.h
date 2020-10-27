#pragma once
#include <iostream>
#include <string>


class readerChecksums
{
public:
    std::string path;

    readerChecksums();

    std::string getString();

    std::string getSongPath();

    std::string getSongId();

    void something();
};


