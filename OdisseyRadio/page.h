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

    void something();

};


