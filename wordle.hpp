#ifndef WORDLE_H
#define WORDLE_H
#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <vector>


//coordinates in ncurses are y, x
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

//idk what our range of coordinates will be yet, (i want it centered, but the format is _ _ _ _ _)
//max y value is unknown rn, moveRight() will have a conditional (can't move more right than 1st dash)
    void moveRight()
    {
        x+=2;
    }

    void moveLeft()
    {
        x-=2;
    }

    void moveDown()
    {
        y++;
        //set x to leftmost value
    }
};

class Wordle
{
    private:
    std::string answer;
    std::string guess; //what the player enters (string format)
    char user_input; //letter entered by user, (concate this to guess for each row)
    int attempts; //how many guesses the player made
    coordinates currentPos;
    std::unordered_map<std::string, std::vector<std::string>> possible_answers; //only winter/christmas related words
    std::unordered_map<std::string, std::vector<std::string>> troll_answers;
    std::unordered_map<std::string, int> valid_guesses; //properly spelled words (all of this in possible answers map too), will delete this if we get a spellcheck api/library working
    //value in maps is a string vector for hints.
    //idk if int is the best value for valid_guesses

    //to do: add helper function to read text file and fill the maps with data

    
    int countLetters(const std::string& s, const char& c) const;

    public:
    Wordle();
    void getGuess();
    void print() const;

    ~Wordle();


};
#endif