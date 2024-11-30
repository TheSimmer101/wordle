# Welcome to Winter Wordleland! ❄️☃️

We participated in the Daedalus Honors The Nightmare Before Christmas Hackathon by creating a winter-themed twist of The NY Times’ Wordle game! 


### Rules of our game:

The rules of the game are the same as the original, except all the possible answers are related to the winter season or winter holidays.

For those who are unfamiliar, this is essentially a word-guessing game.

You have five chances to guess the right word! For each letter in your guess, the color changes depending on how close you are to the answer.

If the letters are:
* Green: the letter is in the correct spot, well done!
* Yellow: the letter is somewhere in the word, but not where you put it.
* White: the letter is not in the word at all.

### Resources:
We have used multiple libraries to create this game, but lucky for you guys, there’s a way to avoid installing all of them to play our game. You can use Docker! 

Docker is a software platform that helped us develop, deploy, and manage our application efficiently by packaging it into containers to ensure consistent performance across various environments. With our Dockerfile, accessing and running our game is quick and easy! This is available for both Linux, Windows, and Mac.

#### Here’s how you can do it:
* Git clone this repository first in your terminal and make it your currently open directory
* Install Docker on your desktop:
  *   Mac: https://docs.docker.com/desktop/setup/install/mac-install/
  *   Windows: https://docs.docker.com/desktop/setup/install/windows-install/
  *   Linux: https://docs.docker.com/desktop/setup/install/linux/
* Run the following commands:
```
docker build -t wordle_repo .
docker run --name wordle_repo_container -it --rm -v ${PWD}/:/workspace -w /workspace wordle_repo
```

Once your docker container is running, the username in the terminal should change to something like 
`root@123456/workspace#` (numbers may vary). Once you have that username, compile and run our game 
with the command `make run`. To exit, press `ctrl` z and type the command `exit`.   For more information, visit the official Docker website: https://www.docker.com/


Here are the other resources we used:
* Ncurses: a library to display the colors in the terminal and update in real-time based on the player's input

* Hunspell: a spell-checking library that ensures players follow Wordle's rule of inputting real words

* LibreOffice English Dictionary: an extension that enhances spell-checking by verifying words against its dictionary. Based on user input, it checks whether a word exists in the dictionary; if it doesn’t, the word is marked as invalid

### HAVE FUN!!!
