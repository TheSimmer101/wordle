#include "wordle.hpp"

Wordle::Wordle()
{
    initscr(); //generates a screen
    noecho(); //user input shows up screen immediately after typed.
    char dash[] = "_ _ _ _ _";

    if(answer.length() == 6)
        char dash[] = "_ _ _ _ _ _";

    mvprintw(10,94,"%s",dash);
    currentPos.x = 94;
    currentPos.y = 10;
    move(currentPos.y,currentPos.x);
    refresh();
    attempts = 0;
    answer = "hello"; //this is a placeholder for now, but it will be a randomly picked word
}
void Wordle::print() const{
    
    refresh();
}

void Wordle::getGuess()
{
    user_input = getch();
    if(user_input == KEY_BACKSPACE)
        currentPos.moveLeft();
    else
    {
        //mvprintw()
        mvprintw(currentPos.y,currentPos.x++,"%c",user_input);
        currentPos.x++;
        currentPos.moveRight();
        //mvprintw(currentPos.y,currentPos.x,"%c",c);
        
    }
}

int Wordle::countLetters(const std::string& s, const char& c) const {
    int count = 0;
    for(char ch : s) {
        if(ch == c) {
            count++;
        }
    }

    return count;
}




Wordle::~Wordle()
{
    endwin();
}
