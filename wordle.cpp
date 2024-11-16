#include "wordle.hpp"

Wordle::Wordle()
{
    // initscr(); //generates a screen
    // noecho(); //user input shows up screen immediately after typed.
    // char dash[] = "_ _ _ _ _";

    // if(answer.length() == 6)
    //     char dash[] = "_ _ _ _ _ _";

    
    // mvprintw(10,94,"%s",dash);
    // currentPos.x = 94;
    // currentPos.y = 10;
    // move(currentPos.y,currentPos.x);
    // refresh();
    // attempts = 0;
    // answer = "hello"; //this is a placeholder for now, but it will be a randomly picked word

    initscr(); // generates a screen
    noecho(); // user input shows up screen immediately after typed.
    answer = "hello"; // this is a placeholder for now, but it will be a randomly picked word
    char dash[answer.length() * 2 - 1]; // generates dash based on length of answer

  
    for (size_t i = 0; i < answer.length(); ++i) {
        dash[i * 2] = '_'; // adds dash
        if (i < answer.length() - 1) {
            dash[i * 2 + 1] = ' '; // adds spaces in between dashes
        }
    }
 
    // gets terminal dimensions to center it
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows/2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    currentPos.x = c;
    currentPos.y = r;

    mvprintw(currentPos.y, currentPos.x, "%s", dash);
    move(currentPos.y, currentPos.x);
    refresh();
    attempts = 0;

    
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
