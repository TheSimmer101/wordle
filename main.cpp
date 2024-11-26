#include <iostream>
#include "wordle.hpp"
#include <hunspell/hunspell.hxx>
// #include <thread>
// #include <chrono> 
using namespace std;


//commands to run docker so hunspell works:
// cd .devcontainer
// docker build -t test_repo .
// docker run --name test_repo_container -it --rm -v ${PWD}/:/workspace -w /workspace test_repo

// If container doesn't open and terminal says "container started", in another terminal run:  docker ps -a to get container id then: docker exec -it \<containerID\>

//credit to Jaime, his instructions here: https://github.com/canizalesjaime/course_335/tree/main/.devcontainer
//i just copy pasted some of his stuff above.


int main()
{

  // Hunspell hunspell("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");

  // cout << "Enter a word: "; 
  // string word = "";
  // cin >> word;
  //   if (hunspell.spell(word)) 
  //       cout << "is correct";
  //   else
  //     cout << "not correct";
  //   cout << endl;
  // initscr();
  // cbreak();
  // refresh();    
  // WINDOW* windowTest = newwin(1, 23, 3, 0);
  // wprintw(windowTest, "Hello World");  
  // wrefresh(windowTest);
  // int ch = getch();
  // if (ch == '\n') {
  //       werase(windowTest);
  //       wrefresh(windowTest);
  //   }
  
  
   
  Wordle w;
  w.loadScreen();
  w.play();
  // delwin(windowTest);
  // clear();
  //endwin();
  //   // endwin();
  //   // clear();
  //   refresh();
//   //  w.getGuess();
//   //  w.getGuess();
//   // w.getGuess();
//   // w.getGuess();
//   // w.getGuess();
//   // // w.print();

//   // getch();
  return 0;


}