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

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
using namespace std;

// 2.3. Linux
// The Linux build only requires linking to -ldl, -lpthread and -lm. You do not need any development packages. You may need to link with -latomic if you're compiling for 32-bit ARM.

int main()
{
    ma_result result;
    ma_engine engine;
    ma_sound sound;

    // Initialize the audio engine
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to initialize the audio engine: " << result << std::endl;
        return -1;
    }

    // Load the sound
    result = ma_sound_init_from_file(&engine, "Theme of Laura.wav", 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to load sound: " << result << std::endl;
        ma_engine_uninit(&engine);
        return -1;
    }

    // Start playing the sound
    result = ma_sound_start(&sound);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to start sound: " << result << std::endl;
        ma_sound_uninit(&sound);
        ma_engine_uninit(&engine);
        return -1;
    }

    std::cout << "Press Enter to quit..." << std::endl;
    std::getchar();

    // Clean up
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);

    return 0;
}
