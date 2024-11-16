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

    
    


    
    // initscr();        // Initializes the ncurses screen
    // noecho();         // Prevents the user input from being echoed on the screen
    // curs_set(0);      // Hides the cursor for a cleaner display

    // // Initialize the answer (you can change this later to be randomly picked)
    // answer = "hello"; // Placeholder answer, which can be replaced later

    // // Create a dash string based on the length of the answer (e.g., _ _ _ _ _ for "hello")
    // std::string dash;
    // for (size_t i = 0; i < answer.length(); ++i) {
    //     dash += "_ ";  // Add underscore and a space for each letter in the answer
    // }
    // dash.pop_back();  // Remove the trailing space to avoid an extra space at the end

    // // Get the terminal dimensions
    // int rows, cols;
    // getmaxyx(stdscr, rows, cols); // Get rows and cols of the terminal

    // // Calculate starting position to center the dash string
    // int start_row = rows / 2;                          // Center the string vertically
    // int start_col = (cols - dash.length()) / 2;        // Center the string horizontally

    // // Set the current position to the center
    // currentPos.x = start_col;
    // currentPos.y = start_row;

    // // Print the centered dash string
    // mvprintw(currentPos.y, currentPos.x, "%s", dash.c_str());

    // // Move the cursor to the starting position
    // move(currentPos.y, currentPos.x);
    
    // // Refresh to display everything on the screen
    // refresh();

    // // Initialize attempts to 0
    // attempts = 0;

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
