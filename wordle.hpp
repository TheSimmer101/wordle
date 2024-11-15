#ifndef WORDLE_H
#define WORDLE_H
#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unordered_map>


//coordinates in ncurses are y, x
struct coordinates
{
    int x;
    int y;

    coordinates(int a, int b)
    {
        x = a;
        y = b;
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
};

class Wordle
{
    private:
    std::string answer;
    std::string guess; //what the player enters (string format)
    char user_input; //letter entered by user, (concate this to guess for each row)
    int attempts; //how many guesses the player made
    coordinates currentPos;
    //to do: add 2 unordered map private variables, one to store all possible guesses, and one for all possible answers

    int countLetters(const std::string& s, const char& c) const;

    public:
    Wordle();
    void print() const;

    ~Wordle();


};
#endif