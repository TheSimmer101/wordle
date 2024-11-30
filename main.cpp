// #include "wordle.hpp"

// // #include <thread>
// // #include <chrono>
// using namespace std;

// // commands to run docker so hunspell works:
// //  cd .devcontainer
// //  docker build -t test_repo .
// //  docker run --name test_repo_container -it --rm -v ${PWD}/:/workspace -w /workspace test_repo

// // If container doesn't open and terminal says "container started", in another terminal run:  docker ps -a to get container id then: docker exec -it \<containerID\>

// // credit to Jaime, his instructions here: https://github.com/canizalesjaime/course_335/tree/main/.devcontainer
// // i just copy pasted some of his stuff above.

// int main()
// {

 

//   Wordle w;
//   w.loadScreen();
//   w.play();

//   getch();
//   return 0;
// }


#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
using namespace std;


// g++ main.cpp -lSDL2 -lSDL2_mixer
int main() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS("Theme of Laura.wav");
    if (!music) {
        std::cerr << "Failed to load music file! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    Mix_PlayMusic(music, 1);

    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}


 