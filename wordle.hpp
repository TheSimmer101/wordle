#ifndef WORDLE_H
#define WORDLE_H
#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <hunspell/hunspell.hxx>
#include <thread>
#include <chrono>

// coordinates in ncurses are y, x
struct coordinates
{
    int x;
    int y;

public:
    coordinates(int a, int b)
    {
        x = a;
        y = b;
    }

    coordinates()
    {
        x = 0;
        y = 0;
    }

    // idk what our range of coordinates will be yet, (i want it centered, but the format is _ _ _ _ _)
    // max y value is unknown rn, moveRight() will have a conditional (can't move more right than 1st dash)
    void moveRight()
    {
        // // {   int rows, cols;
        // //     getmaxyx(stdscr, rows, cols);

        // //     int r = rows / 2;

        // //     int c = (cols - 5) / 2;

        if (x != 20)
            x += 2;
        else
        {
            y++;
            x = 114;
        }
    }

    void moveLeft()
    {
        x -= 2;
    }

    void moveDown()
    {
        y++;

        // x =
        //  set x to leftmost value
    }
};

class Wordle
{
private:
    int leftmost_x;
    int rightmost_x;

    std::string answer;
    std::string guess; // what the player enters (string format)
    int user_input;    // letter entered by user, (concate this to guess for each row)
    int attempts;      // how many guesses the player made
    coordinates currentPos;
    std::unordered_map<int, std::string> possible_answers; // only winter/christmas related words
    std::unordered_map<std::string, std::vector<std::string>> troll_answers;
    std::unordered_map<std::string, int> valid_guesses; // properly spelled words (all of this in possible answers map too), will delete this if we get a spellcheck api/library working
    // value in maps is a string vector for hints.
    // idk if int is the best value for valid_guesses

    // to do: add helper function to read text file and fill the maps with data
    //
    enum colors
    {
        green,
        yellow,
        white
    };
    std::vector<Wordle::colors> getColors(const std::string &guess) const; // returns a vector that shows color for each letter in user guess, for example if guess == answer then vector should be {green, green, green..}
    int countLetters(const std::string &s, const char &c, const int &startIndex) const;
    int charIndex(const std::string &str, const char &c,const int &startIndex) const; // returns the 1st index that char c appears in string. -1 if letter doesn't appear

public:
    Wordle();
    std::string getGuess();
    std::string getGuess(coordinates startPos);
    void play();
    void print() const;
    bool realWord(const std::string &guess) const; // helper function to check if the word is an actual word in the dictionary
    void loadScreen();

    ~Wordle();
};
#endif