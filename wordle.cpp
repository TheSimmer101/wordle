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
    init_pair(4, COLOR_WHITE, COLOR_BLUE);  // Blue loading screen

    // CREATE POSSIBLE ANSWER HASHMAP
    std::ifstream infile; // creates variable for file to open for reading
    infile.open("wordlist.txt");

    if (infile.fail())
    {
        // std::cerr << "File cannot be opened for reading.";
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
    answer = "JOLLY";
   // answer = possible_answers[1];
    attempts = 0;

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows / 2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    // // instructions for game
    // mvprintw(r - 8, c - 40, "Here's how you play:");
    // mvprintw(r - 7, c - 40, "You have five chances to guess the right word!");
    // mvprintw(r - 6, c - 40, "For each letter in your guess, the color changes depending on how close you are to the answer.");
    // mvprintw(r - 5, c - 40, "If the letter is green: the letter is in the correct spot, well done!");
    // mvprintw(r - 4, c - 40, "If the letter is yellow: the letter is somewhere in the word, but not where you put it");
    // mvprintw(r - 3, c - 40, "If the letter is gray: the letter is not in the word at all, tough");
    // mvprintw(r - 2, c - 40, "Have fun!");

    // char dash[dash_length + 1];
    // for (size_t i = 0; i < answer.length(); ++i)
    // {
    //     dash[i * 2] = '_';
    //     if (i < answer.length() - 1)
    //     {
    //         dash[i * 2 + 1] = ' ';
    //     }
    // }
    // dash[dash_length] = '\0';

    // for (int i = 0; i < 5; ++i)
    // {
    //     mvprintw(r + i, c, "%s", dash);
    // }

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

        if ((guess.length() == answer.length()) && (user_input == KEY_ENTER || user_input == '\n'))
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
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows / 2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    // instructions for game
    mvprintw(r - 12, c - 40, "Here's how you play:");
    mvprintw(r - 11, c - 40, "You have five chances to guess the right word!");
    mvprintw(r - 10, c - 40, "For each letter in your guess, the color changes depending on how close you are to the answer.");
    mvprintw(r - 8, c - 40, "If the letter is green: the letter is in the correct spot, well done!");
    mvprintw(r - 7, c - 40, "If the letter is yellow: the letter is somewhere in the word, but not where you put it");
    mvprintw(r - 6, c - 40, "If the letter is gray: the letter is not in the word at all");
    mvprintw(r - 4, c - 40, "Have fun!");

    
    const char* ascii_art_2[] = {
         ".      *    *           *.       *   .                      *     .",
        "               .   .                   __   *    .     * .     *",
        "    *       *         *   .     .    _|__|_        *    __   .       *",
        "  .  *  /\\       /\\          *        ('')    *       _|__|_     .",
        "       /  \\   * /  \\  *          .  <( . )> *  .       ('')   *   *",
        "  *    /  \\     /  \\   .   *       _(__.__)_  _   ,--<(  . )>  .    .",
        "      /    \\   /    \\          *   |       |  )),`   (   .  )     *",
        "   *   `||` ..  `||`   . *.   ... ==========='`   ... '--`-` ... * .",
    nullptr
    };


    // have the ascii snowman art be displayed at the bottom corner right
    int offset_y1 = 4; 
    int offset_x1 = 8; 

    int art_start_y1 = rows - 6 - offset_y1;
    int art_start_x1 = cols - strlen(ascii_art_2[0]) - offset_x1;

    for (int i = 0; ascii_art_2[i] != nullptr; i++) {
        mvprintw(art_start_y1 + i, art_start_x1, ascii_art_2[i]);
    }

    
    const char* ascii_art_3[] = {
        "                                                   __.  .--,",
    "*-/___,  ,-/___,-/___,-/___,-/___,           _.-.=,{\\/ _/  /`)",
    " `\\ _ ),-/___,-/___,-/___,-/___, )     _..-'`-(`._(_.;`   /",
    "  /< \\\\=`\\ _ )`\\ _ )`\\ _ )`\\ _ )<`--''`     (__\\_________/___,",
    "         /< <\\ </ /< /< /< </ /<           (_____Y_____Y___,",
    
        nullptr
    };

    // have the ascii santa-sleigh art be displayed at the bottom corner left
    int offset_y2 = 1; 
    int offset_x2 = 2; 

    int art_start_y2 = rows - 6 - offset_y2;
    int art_start_x2 = offset_x2;

    for (int i = 0; ascii_art_3[i] != nullptr; i++) {
        mvprintw(art_start_y2 + i, art_start_x2, ascii_art_3[i]);
    }

    
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

//main code for getting guess & ensuring it's valid, then printing with colors
    for (int i = 1; i <= 5; i++)
    {
        guess = getGuess(currentPos);
        std::vector<Wordle::colors> colorVec = getColors(guess);
        move(currentPos.y, leftmost_x);
        if (guess == answer)
        {
            for (int i = 0; i < guess.length(); i++)
            {
                attron(COLOR_PAIR(1));
                mvprintw(currentPos.y, currentPos.x, "%c", guess[i]);
                currentPos.moveRight();
                move(currentPos.y, currentPos.x);
                attroff(COLOR_PAIR(1));
            }
            i = 6;
        }
        else
        {
            for (int colorIndex = 0; colorIndex < guess.length(); colorIndex++)
            {
                if (colorVec[colorIndex] == green)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(currentPos.y, currentPos.x, "%c", guess[colorIndex]);
                    currentPos.moveRight();
                    move(currentPos.y, currentPos.x);
                    attroff(COLOR_PAIR(1));
                }
                else if (colorVec[colorIndex] == yellow)
                {
                    attron(COLOR_PAIR(2));
                    mvprintw(currentPos.y, currentPos.x, "%c", guess[colorIndex]);
                    currentPos.moveRight();
                    move(currentPos.y, currentPos.x);
                    attroff(COLOR_PAIR(2));
                }
                else if (colorVec[colorIndex] == white)
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(currentPos.y, currentPos.x, "%c", guess[colorIndex]);
                    currentPos.moveRight();
                    move(currentPos.y, currentPos.x);
                    attroff(COLOR_PAIR(3));
                }
            }
            currentPos.x = c;
            currentPos.y = r + i;
            move(currentPos.y, currentPos.x);

        }
    }


    move(r+6, c-6);
    std::string revealAnswer = "The word is: " + answer;
    if(guess == answer)
    {
        printw("Yay! You guessed correctly! :D");
    }
                
    else
        {
            printw("Aw, you didn't get the word!");
            mvprintw(r+7, c-6, revealAnswer.c_str());
        }

    move(r + 9, c-12);
    printw("Would you like to play again? (Use arrow keys): Y/N");        
}

// helper function to display ascii art in loading screen
// i tried to use it in gameplay screen but it wasn't turning out well
// void Wordle::displayAsciiArt(WINDOW *win, const char* ascii_art[], int start_y = 9) {
//     // prints ascii art
//     int y = start_y; 
//     for (int i = 0; ascii_art[i] != nullptr; ++i) {
//         mvwprintw(win, y++, 0, ascii_art[i]);
//     }

//     wrefresh(win);
// }

void Wordle::loadScreen()
{
    // credit: https://stackoverflow.com/questions/67514610/how-do-i-make-a-welcome-screen-using-ncurses-that-leads-into-my-code
    initscr();
    cbreak();
    refresh();

    WINDOW *windowTest = newwin(30, 100, 6, 60);
    int text_startx = (60 - strlen("hello world")) / 2; // put some text to help with centering
    
    mvwprintw(windowTest, 1, text_startx - 7, "Welcome to Winter Wordleland!");
    mvwprintw(windowTest, 3, text_startx - 4, "Loading... Please wait");

   // display this cute winter scenery in loading page
   const char* ascii_art_1[] = {
        "   .-.                                                   \\ /",
        "  ( (                                |                  - * -",
        "   '-`                              -+-                  / \\",
        "            \\            o          _|_          \\",
        "            ))          }^{        /___\\         ))",
        "          .-#-----.     /|\\     .---'-'---.    .-#-----.",
        "     ___ /_________\\   //|\\\\   /___________\\  /_________\\",
        "    /___\\ |[] _ []|    //|\\\\    | A /^\ A |    |[] _ []| _.O,_",
        "....|\"#\"|.|  |*|  |...///|\\\\\\...|   |\"|   |....|  |*|  |..(^)....",
        nullptr
    };
   

    int start_y = 9;
    for (int i = 0; ascii_art_1[i] != nullptr; i++) {
        mvwprintw(windowTest, start_y + i, 0, ascii_art_1[i]);
    }

    // loading bar
    int bar_width = 40;
    int bar_startx = (80 - bar_width) / 4;
    int bar_y = 5;

    mvwprintw(windowTest, bar_y, bar_startx, "[%s]", std::string(bar_width, ' ').c_str());
    wrefresh(windowTest);

    for (int i = 0; i < bar_width; i++)
    {
        mvwaddch(windowTest, bar_y, bar_startx + 1 + i, '=');
        wrefresh(windowTest);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    werase(windowTest);
    wrefresh(windowTest);
    delwin(windowTest);
    refresh();
  
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

int Wordle::charIndex(const std::string &str, const char &c,const int &startIndex) const
{
    for (int i = startIndex; i < str.length(); i++)
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

std::vector<Wordle::colors> Wordle::getColors(const std::string &guess) const
{
    //list the quantity of each letter present in answer and guess, (e.g. candy has 1 c, 1 a, 1 n, etc.)
    std::unordered_map<char, int> answerLettersCount;
    std::unordered_map<char, int> guessLettersCount;

    for(int x = 0; x < guess.length();x++)
    {
        answerLettersCount[answer[x]]++;
        guessLettersCount[guess[x]]++;
    }
    std::vector<Wordle::colors> result(guess.length(),white); //declares vector of size guessLength and fills it with white

//TESTING
// answer: JOLLY  (2 L's), this is already set in constructor rn
// guess: LOLLY   (3 L's)
// colors should be: 1st L is WHITE, everything else GREEN
//problem: 1st L is yellow, which is wrong. (OLLY is green, which is good!)
//yellow implies you can move that letter somewhere else to get answer, but yellow L then all green OLLY contradicts that idea.
//only the 1st letter is wrong, but you can't move it to another position since we know OLLY is the fully correct part



//if letter is in the right spot mark it green, and decrement that letter count in guess map
// green letters have priority
    for (int k = 0; k < guess.length(); k++)
    {
        if(guess[k] == answer[k])
        {
            result[k] = green;
            answerLettersCount[guess[k]]--;
        }
            
        
        // might need to modify case for yellow, for example answer = "jolly", and guess = "local", both l's would need to be yellow
          
                
        
        // else if (charIndex(answer, letter) == k)
        //     result.push_back(green);
    }
    for (int j = 0; j < guess.length(); j++)
    {
        //letter not in right position and quantity of letter in guess is less than its quantity in answer
        if (guess[j] != answer[j] && guessLettersCount[guess[j]]!= 0 && guessLettersCount[guess[j]] <= answerLettersCount[guess[j]]) 
            {
                
                result[j] = yellow;
                guessLettersCount[guess[j]]--;
            }
    }
    
    return result;
}

Wordle::~Wordle()
{
    endwin();
}