#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "texture.h"
#include "timer.h"
#include "tile.h"
#include "auxFunctions.h"
#include "Player.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
int main(int argc,char *argv[]){
    if(string(argv[1]) == "server"){

    }
    else if(string(argv[1]) == "client"){

    }
    else {
        std :: cerr << "invalid command line argument passed. Please select either a server or a client.\n";
    }
}