#include "wordle.hpp"

// #include <thread>
// #include <chrono>
using namespace std;

// // commands to run docker so hunspell works:

// //  docker build -t test_repo .
// //  docker run --name test_repo_container -it --rm -v ${PWD}/:/workspace -w /workspace test_repo

// // If container doesn't open and terminal says "container started", in another terminal run:  docker ps -a to get container id then: docker exec -it \<containerID\>

// // credit to Jaime, his instructions here: https://github.com/canizalesjaime/course_335/tree/main/.devcontainer


int main()
{
  Wordle w;
  w.play();
  // w.endScreen();

  getch();
  return 0;
}



 