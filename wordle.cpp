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
    // raw();
    // intrflush(stdscr, FALSE); // this stops the program to stop running when an interrupt key is read
    keypad(stdscr, true);               // allows keypad input
    noecho();                           // user input shows up screen immediately after typed.
    answer = "hello";                   // this is a placeholder for now, but it will be a randomly picked word
    char dash[answer.length() * 2 - 1]; // generates dash based on length of answer

    for (size_t i = 0; i < answer.length(); ++i)
    {
        dash[i * 2] = '_'; // adds dash
        if (i < answer.length() - 1)
        {
            dash[i * 2 + 1] = ' '; // adds spaces in between dashes
        }
    }

    // gets terminal dimensions to center it
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows / 2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    currentPos.x = c;
    currentPos.y = r;

    mvprintw(currentPos.y, currentPos.x, "%s", dash);
    move(currentPos.y, currentPos.x);
    refresh();
    attempts = 0;
}
void Wordle::print() const
{

    refresh();
}

void Wordle::getGuess()
{

    user_input = getch();
    if (user_input == KEY_BACKSPACE)
    {
        if (!guess.empty())
        {
            guess = guess.substr(0, guess.length() - 1);
            currentPos.moveLeft();
            move(currentPos.y, currentPos.x);
            mvprintw(currentPos.y, currentPos.x, "%c", '_');
            move(currentPos.y, currentPos.x);
        }
    }
    else
    {
        guess += user_input;
        mvprintw(currentPos.y, currentPos.x, "%c", user_input);
        // currentPos.x++;
        currentPos.moveRight();
        move(currentPos.y, currentPos.x);
        // mvprintw(currentPos.y,currentPos.x,"%c",c);
    }
}

void Wordle::play()
{
    bool finalGuess = false; // this is the word they want to enter after all inputs
    for (int i = 0; i < 5; i++)
    {
        // this is to get each char for their word until they get their final answer
        // to do:
        // allow them to enter the answer instead of just accepting it at the word length
        while (!finalGuess)
        {
            getGuess();
            if (guess.length() == answer.length())
            {
                finalGuess = true;
            }
        }

        // this is to check if the guess is correct. if it is, exits the loop
        // if it isn't, it continues the guesses and their guess resets
        if (guess == answer)
        {
            i = 5;
        }
        else
        {
            finalGuess = false;
            guess = "";
            // to do
            // start a new line with new dashes
        }
    }
}

// checks if it's a real word
bool Wordle::realWord(const std::string &guess) const
{
    return false;
}

int Wordle::charIndex(const std::string &str, const char &c) const
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
            return i;
    }
    return -1;
}
int Wordle::countLetters(const std::string &s, const char &c, const int &startIndex) const
{
    int count = 0;
    for (char ch : s)
    {
        if (ch == c)
        {
            count++;
        }
    }

    return count;
}

std::vector<Wordle::colors> Wordle::getColors(const std::string guess) const
{
    std::vector<Wordle::colors> result = {};

    for (int k = 0; k < guess.length(); k++)
    {
        char letter = guess[k];
        if (countLetters(answer, letter, 0) == 0) // letter not in string at all
            result.push_back(white);
        else if (charIndex(answer, letter) != k) // might need to modify case for yellow, for example answer = "jolly", and guess = "local", both l's would need to be yellow
        {
            result.push_back(yellow);
        }
        else if (charIndex(answer, letter) == k)
            result.push_back(green);
    }

    return result;
}

Wordle::~Wordle()
{
    endwin();
}
