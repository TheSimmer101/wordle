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

    // initscr(); // generates a screen
    // // raw();
    // // intrflush(stdscr, FALSE); // this stops the program to stop running when an interrupt key is read
    // keypad(stdscr, true);               // allows keypad input
    // noecho();                           // user input shows up screen immediately after typed.
    // answer = "hello";                   // this is a placeholder for now, but it will be a randomly picked word
    // // char dash[answer.length() * 2 - 1]; // generates dash based on length of answer

    // // for (size_t i = 0; i < answer.length(); ++i)
    // // {
    // //     dash[i * 2] = '_'; // adds dash
    // //     if (i < answer.length() - 1)
    // //     {
    // //         dash[i * 2 + 1] = ' '; // adds spaces in between dashes
    // //     }
    // // }

    // // gets terminal dimensions to center it

    // char dash[] = "_ _ _ _ _";

    // if(answer.length() == 6)
    //     char dash[] = "_ _ _ _ _ _";

    // int rows, cols;
    // getmaxyx(stdscr, rows, cols);

    // int r = rows / 2;
    // int dash_length = answer.length() * 2 - 1;
    // int c = (cols - dash_length) / 2;
    // std::cout << "\n\nrow: " << r;
    // //std::cout << "\n col: " << c;
    // currentPos.x = c;
    // currentPos.y = r;

    // //hello there
    // int row = 14;
    // for(int i = 0; i < 5; i++)
    // {

    //     mvprintw(row, 114, "%s", dash);
    //     row++;
    //     //mvprintw(currentPos.y, currentPos.x, "%s", dash);
    //     currentPos.y++;
    // }
    // currentPos.y = r;
    // move(currentPos.y, currentPos.x);
    // refresh();
    // attempts = 0;

    initscr();
    keypad(stdscr, true);
    noecho(); // stop it from showing all characters typed in

    int rowMAX, colMAX;
    getmaxyx(stdscr, rowMAX, colMAX);

    int dashes_length = answer.length() * 2 - 1;
    leftmost_x = (colMAX - dashes_length) / 2;
    rightmost_x = leftmost_x + dashes_length - 1; // last dash

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Pair 1: Green text on black background
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    // CREATE POSSIBLE ANSWER HASHMAP
    std::ifstream infile; // creates variable for file to open for reading
    infile.open("wordlist.txt");

    if (infile.fail())
    {
        std::cerr << "File cannot be opened for reading.";
        exit(1); // exit if failed to open the file
    }
    std::string line = ""; // holding a line from txt file for value
    int pos = 1;           // holding pos for key
    while (getline(infile, line))
    {
        possible_answers[pos] = line;
        pos++;
    }

    // generate random position
    srand(time(0));
    int randomPos = 1 + rand() % 106;
    answer = possible_answers[1];
    attempts = 0;

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows / 2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    // instructions for game
    mvprintw(r - 8, c - 40, "Here's how you play:");
    mvprintw(r - 7, c - 40, "You have five chances to guess the right word!");
    mvprintw(r - 6, c - 40, "For each letter in your guess, the color changes depending on how close you are to the answer.");
    mvprintw(r - 5, c - 40, "If the letter is green: the letter is in the correct spot, well done!");
    mvprintw(r - 4, c - 40, "If the letter is yellow: the letter is somewhere in the word, but not where you put it");
    mvprintw(r - 3, c - 40, "If the letter is gray: the letter is not in the word at all, tough");
    mvprintw(r - 2, c - 40, "Have fun!");

    char dash[dash_length + 1];
    for (size_t i = 0; i < answer.length(); ++i)
    {
        dash[i * 2] = '_';
        if (i < answer.length() - 1)
        {
            dash[i * 2 + 1] = ' ';
        }
    }
    dash[dash_length] = '\0';

    for (int i = 0; i < 5; ++i)
    {
        mvprintw(r + i, c, "%s", dash);
    }

    currentPos.x = c;
    currentPos.y = r;
    move(currentPos.y, currentPos.x);
    refresh();
}

void Wordle::print() const
{

    refresh();
}

std::string Wordle::getGuess()
{

    // user_input = getch();
    // if (user_input == KEY_BACKSPACE)
    // {
    //     if (!guess.empty())
    //     {
    //         guess = guess.substr(0, guess.length() - 1);
    //         currentPos.moveLeft();
    //         move(currentPos.y, currentPos.x);
    //         mvprintw(currentPos.y, currentPos.x, "%c", '_');
    //         move(currentPos.y, currentPos.x);
    //     }
    // }
    // else
    // {
    //     guess += user_input;
    //     mvprintw(currentPos.y, currentPos.x, "%c", user_input);
    //     // currentPos.x++;
    //     currentPos.moveRight();
    //     move(currentPos.y, currentPos.x);
    //     // mvprintw(currentPos.y,currentPos.x,"%c",c);
    // }

    // user_input = getch();
    // const int BACKSPACE_KEY = 127; // ascii key for delete character, adjust if your terminal uses a different code for backspace

    // if (user_input == BACKSPACE_KEY || user_input == KEY_BACKSPACE)
    // {
    //     if (!guess.empty())
    //     {
    //         guess = guess.substr(0, guess.length() - 1);
    //         currentPos.moveLeft();
    //         move(currentPos.y, currentPos.x);
    //         addch('_'); // replace backspace with dash
    //         move(currentPos.y, currentPos.x);
    //     }
    // }
    // else
    // {
    //     guess += user_input;
    //     mvprintw(currentPos.y, currentPos.x, "%c", user_input);
    //     currentPos.moveRight();
    //     move(currentPos.y, currentPos.x);
    // }

    guess = "";

    const int BACKSPACE_KEY = 127; // ascii key for delete character

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int dash_length = answer.length() * 2 - 1;
    leftmost_x = (cols - dash_length) / 2;
    rightmost_x = leftmost_x + dash_length - 1; // last dash

    while (guess.length() != answer.length())
    {
        user_input = getch();

        if (user_input == BACKSPACE_KEY || user_input == KEY_BACKSPACE)
        {
            if (!guess.empty())
            {
                guess = guess.substr(0, guess.length() - 1);
                currentPos.moveLeft();
                move(currentPos.y, currentPos.x);
                addch('_'); // replace backspace with dash
                move(currentPos.y, currentPos.x);
            }
        }
        else if (user_input == KEY_ENTER || user_input == '\n') // if user presses enter
        {
            if (currentPos.x == rightmost_x) // current position is on last dash
            {
                currentPos.y++;            // moves to next row
                currentPos.x = leftmost_x; // current position goes to leftmost dash
                move(currentPos.y, currentPos.x);
                refresh();
                return guess;
            }
        }
        else
        {
            guess += toupper(user_input);
            mvprintw(currentPos.y, currentPos.x, "%c", toupper(user_input));
            currentPos.moveRight();

            if (currentPos.x > rightmost_x)
            {
                currentPos.y++;
                currentPos.x = leftmost_x;
            }
            move(currentPos.y, currentPos.x);
        }
    }
    return guess;
}

std::string Wordle::getGuess(coordinates startPos)
{
    Hunspell hunspell("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
    bool finalguess = false;
    guess = "";

    const int BACKSPACE_KEY = 127;
    while (!finalguess)
    {
        user_input = getch();
        if (isalpha(user_input) && guess.length() < answer.length()) // if input is a letter, add uppercase to guess and print the letter
        {
            user_input = toupper(user_input);
            guess += toupper(user_input);
            mvprintw(startPos.y, startPos.x, "%c", user_input);
            startPos.moveRight();
            move(startPos.y, startPos.x);
            // guess += toupper(user_input);
            // printw("%c",toupper(user_input));
            // startPos.moveRight();
        }
        else if (user_input == BACKSPACE_KEY || user_input == KEY_BACKSPACE)
        {
            if (!guess.empty())
            {
                guess = guess.substr(0, guess.length() - 1);
                startPos.moveLeft();
                move(startPos.y, startPos.x);
                addch('_'); // replace backspace with dash
                move(startPos.y, startPos.x);
            }
        }

        if (guess.length() == answer.length() && user_input == KEY_ENTER || user_input == '\n')
        {
            if (!hunspell.spell(guess))
            {
                move(startPos.y, startPos.x + 5);
                printw("%s", "Please enter a valid word!");
            }
            else
            {
                finalguess = true;
            }
        }
    }
    return guess;
}

void Wordle::play()
{
    // printw("Hello, world!\n");
    getGuess(currentPos);
    // //bool finalGuess = false; // this is the word they want to enter after all inputs
    // for (int i = 0; i < 5; i++)
    // {
    //     // this is to get each char for their word until they get their final answer
    //     // to do:
    //     // allow them to enter the answer instead of just accepting it at the word length
    //     // while (!finalGuess)
    //     // {
    //         guess = "";
    //         getGuess();
    //     //     if (guess.length() == answer.length())
    //     //     {
    //     //         finalGuess = true;
    //     //     }
    //     // }
    //     std::vector<Wordle::colors> c = getColors(guess);
    //     move(currentPos.y, leftmost_x);
    //     for(int i = 0; i < guess.length(); i++)
    //     {
    //         if(c[i] == green)
    //         {
    //             attron(COLOR_PAIR(1));
    //             printw("%c",guess[i]);
    //             attroff(COLOR_PAIR(1));

    //         }

    //     }

    //     // this is to check if the guess is correct. if it is, exits the loop
    //     // if it isn't, it continues the guesses and their guess resets
    //     if (guess == answer)
    //     {
    //         break;
    //     }
    //     else
    //     {
    //         //finalGuess = false;
    //         guess = "";
    //         // to do
    //         // start a new line with new dashes

    //         // currentPos.y += 1;

    //         // // generate a new line of dashes
    //         // char dash[answer.length() * 2 - 1];
    //         // for (size_t j = 0; j < answer.length(); ++j)
    //         // {
    //         //     dash[j * 2] = '_'; // Add dash
    //         //     if (j < answer.length() - 1)
    //         //     {
    //         //         dash[j * 2 + 1] = ' ';
    //         //     }
    //         // }
    //         // mvprintw(currentPos.y, currentPos.x, "%s", dash);
    //         // move(currentPos.y, currentPos.x);
    //         // refresh();
    //     }
    // }

    // mvprintw(100,100, "%s", "yay you did it!");
}

// checks if it's a real word
bool Wordle::realWord(const std::string &guess) const
{
    // Hunspell hunspell("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");

    // while (true)
    // {
    //     user_input = getch();
    //     if (user_input == KEY_ENTER || user_input == '\n' && hunspell.spell(guess) == true)
    //     {
    //         return guess;
    //     }
    //     else if (hunspell.spell(guess) == false)
    //     {
    //         move(startPos.y, startPos.x + 5);
    //         printw("%s", "Please enter a valid word!");
    //         user_input = getch();

    //         if (user_input == BACKSPACE_KEY || user_input == KEY_BACKSPACE)
    //         {

    //             if (!guess.empty())
    //             {
    //                 guess = guess.substr(0, guess.length() - 1);
    //                 startPos.moveLeft();
    //                 move(startPos.y, startPos.x);
    //                 addch('_'); // replace backspace with dash
    //                 move(startPos.y, startPos.x);
    //             }
    //         }
    //     }
    // }
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