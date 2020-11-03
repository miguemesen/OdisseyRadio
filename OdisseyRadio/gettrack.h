#pragma once
#include <iostream>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <unistd.h>
#include <string>
#include <sstream>
#define sout(x) std::cout<<x<<std::endl;

class getTrack
{
public:
    void musicPosition(double position);
    getTrack();
};


