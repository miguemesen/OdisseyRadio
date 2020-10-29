#pragma once
#include <iostream>
#include "song.h"
#include "readerchecksums.h"
#include "LinkedList.h"


class page
{
public:
    page();

    LinkedList<song> myPage;

    std::vector<song> mySongs[5];

    void something();

};


