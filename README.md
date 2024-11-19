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

*These are available for both Linux, Windows, and Mac. <br/>
See the installation guide for your device if not already installed.



To compile and run:
  Inside the directory where this repository is stored, type "make run" in the terminal (without quotes).
  make clean to remove executable files.
  


ncurses was used here to display colors in the terminal, as well as update in real-time with the player's input.
