Built for the Fall 2024 Daedalus Hackathon!
Theme: Winter Wonderland

Using the ncurses library with C++, we recreated New York Times' Wordle. 
For those who are unfamiliar, this is essentially a word guessing game.

You have five chances to guess the right word!
For each letter in your guess, the color changes depending on how close you are to the answer. <br/>
If the letter is <br/>
&nbsp;&nbsp;&nbsp;&nbsp;Green: the letter is in the correct spot, well done! <br/>
&nbsp;&nbsp;&nbsp;&nbsp;Yellow: the letter is somewhere in the word, but not where you put it. <br/>
&nbsp;&nbsp;&nbsp;&nbsp;Gray/Black: the letter is not in the word at all, tough. <br/>


Requirements:
- C++ Compiler (g++)
- ncurses library
- Makefile
- Hunspell

*These are available for both Linux, Windows, and Mac. <br/>
See the installation guide for your device if not already installed.

Alternative:
Don't have the above resources installed? Don't want to? We got you covered! 
Try Docker! With our dockerfile you don't have to deal with installing these libraries.
Be sure to clone this git repository first and make it your currently open directory.
Simply install Docker on your computer and then run the following commands:
(Docker is only needed to be installed once for every computer)
docker build -t wordle_repo .
docker run --name wordle_repo_container -it --rm -v ${PWD}/:/workspace -w /workspace wordle_repo

Once your docker container is running, the username in the terminal should change to something like root@123456/workspace# (numbers may vary).
While docker is running, compile and run the code as usual (make run).
To exit out of the docker container, simply type "exit" into your terminal without the quotation marks.
For more information, visit the official Docker website: https://www.docker.com/

To compile and run:
  Inside the directory where this repository is stored, type "make run" in the terminal (without quotes).
  make clean to remove executable files.
  


ncurses was used here to display colors in the terminal, as well as update in real-time with the player's input.
Hunspell is a spell checking library. Wordle requires a real word to be inputted, so players cannot enter something like abcde.