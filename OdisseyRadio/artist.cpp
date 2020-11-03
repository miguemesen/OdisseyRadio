#include "artist.h"
#include <iostream>
//#define log(x) std::cout<<x<<std::endl;

artist::artist()
{
    songs = new LinkedList<song>();
}
