#include "wordle.hpp"

Wordle::Wordle()
{
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
    init_pair(4, COLOR_WHITE, COLOR_BLUE); // Blue loading screen

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
    int randomPos = 1 + rand() % 105;

    answer = possible_answers[randomPos];
    attempts = 0;

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = rows / 2;
    int dash_length = answer.length() * 2 - 1;
    int c = (cols - dash_length) / 2;

    currentPos.x = c;
    currentPos.y = r;
    move(currentPos.y, currentPos.x);
    refresh();
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
                refresh();
            }
            else
            {
                move(startPos.y, startPos.x + 5);
                clrtoeol();
                refresh();
                finalguess = true;
            }
        }
    }
    return guess;
}

void Wordle::play()
{
   // clear();
    
    const char *choices[] = {
        "Yes",
        "No",
    };

    int highlight = 0;
    int choice = 0;

    while(choices[highlight] == "Yes")
    {
    loadScreen();
    int randomPos = 1 + rand() % 105;
    answer = possible_answers[randomPos];
    curs_set(1);
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
    mvprintw(r - 6, c - 40, "If the letter is white: the letter is not in the word at all");
    mvprintw(r - 4, c - 40, "Have fun!");

    const char *ascii_art_2[] = {
        ".      *    *           *.       *   .                      *     .",
        "               .   .                   __   *    .     * .     *",
        "    *       *         *   .     .    _|__|_        *    __   .       *",
        "  .  *  /\\       /\\          *        ('')    *       _|__|_     .",
        "       /  \\   * /  \\  *          .  <( . )> *  .       ('')   *   *",
        "  *    /  \\     /  \\   .   *       _(__.__)_  _   ,--<(  . )>  .    .",
        "      /    \\   /    \\          *   |       |  )),`   (   .  )     *",
        "   *   `||` ..  `||`   . *.   ... ==========='`   ... '--`-` ... * .",
        nullptr};

    // have the ascii snowman art be displayed at the bottom corner right
    int offset_y1 = 3;
    int offset_x1 = 8;

    int art_start_y1 = rows - 6 - offset_y1;
    int art_start_x1 = cols - strlen(ascii_art_2[0]) - offset_x1;

    for (int i = 0; ascii_art_2[i] != nullptr; i++)
    {
        mvprintw(art_start_y1 + i, art_start_x1, ascii_art_2[i]);
    }

    const char *ascii_art_3[] = {
        "                                                   __.  .--,",
        "*-/___,  ,-/___,-/___,-/___,-/___,           _.-.=,{\\/ _/  /`)",
        " `\\ _ ),-/___,-/___,-/___,-/___, )     _..-'`-(`._(_.;`   /",
        "  /< \\\\=`\\ _ )`\\ _ )`\\ _ )`\\ _ )<`--''`     (__\\_________/___,",
        "         /< <\\ </ /< /< /< </ /<           (_____Y_____Y___,",

        nullptr};

    // have the ascii santa-sleigh art be displayed at the bottom corner left
    int offset_y2 = 0;
    int offset_x2 = 2;

    int art_start_y2 = rows - 6 - offset_y2;
    int art_start_x2 = offset_x2;

    for (int i = 0; ascii_art_3[i] != nullptr; i++)
    {
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

    for (int i = 0; i < answer.length(); ++i)
    {
        mvprintw(r + i, c, "%s", dash);
    }

    currentPos.x = c;
    currentPos.y = r;
    move(currentPos.y, currentPos.x);
    refresh();


    // main code for getting guess & ensuring it's valid, then printing with colors
    for (int i = 1; i <= answer.length(); i++)
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

    int centerCol = cols / 2;
    int lineSpace = 2;

    if (guess == answer) {
        mvprintw(r + 7, centerCol - 16, "Yay! You guessed correctly! :D");
    } else {
        mvprintw(r + 7, centerCol - 13, "Aw, you didn't get the word!");
        std::string revealAnswer = "The word is: " + answer;
        mvprintw(r + 7 + lineSpace, centerCol - revealAnswer.length() / 2, "%s", revealAnswer.c_str());
    }

    std::string prompt = "Would you like to play again?";
    mvprintw(r + 7 + 2 * lineSpace, centerCol - prompt.length() / 2, "%s", prompt.c_str());


    
    currentPos.y = r + 8 + 2 * lineSpace;
    currentPos.x = centerCol - prompt.length() + 24;

    //mvprintw(currentPos.y, currentPos.x, "%s", choices[0]);
    // mvprintw(currentPos.y + 1, currentPos.x + 3, "%s", choices[1]);
    curs_set(0);
    while(true)
    {
        for(int i = 0; i < 2; i++)
        {
            if(i == highlight)
            {
                wattron(stdscr, A_REVERSE);
            }
            mvprintw(currentPos.y + i, currentPos.x, "%s", choices[i]);
          //  mvprintw(currentPos.y + 2, currentPos.x, "%s", choices[1]);
            wattroff(stdscr, A_REVERSE);
        }
        choice = getch();

        if(choice == KEY_UP)
        {
            highlight--;
            if(highlight == -1)
                highlight++;
        }
        else if (choice == KEY_DOWN)
        {
            highlight++;
            if(highlight == 2)
                highlight--;
        }   
        else if(choice == 10 || choice == KEY_ENTER || user_input == '\n' )
            break;
    }
    if(choices[highlight] == "Yes")
        clear();
    }
    if(choices[highlight] == "No") {
        endScreen();
    }
    
    
}

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
    const char *ascii_art_1[] = {
        "   .-.                                                   \\ /",
        "  ( (                                |                  - * -",
        "   '-`                              -+-                  / \\",
        "            \\            o          _|_          \\",
        "            ))          }^{        /___\\         ))",
        "          .-#-----.     /|\\     .---'-'---.    .-#-----.",
        "     ___ /_________\\   //|\\\\   /___________\\  /_________\\",
        "    /___\\ |[] _ []|    //|\\\\    | A /^\ A |    |[] _ []| _.O,_",
        "....|\"#\"|.|  |*|  |...///|\\\\\\...|   |\"|   |....|  |*|  |..(^)....",
        nullptr};

    int start_y = 10;
    for (int i = 0; ascii_art_1[i] != nullptr; i++)
    {
        mvwprintw(windowTest, start_y + i, 0, ascii_art_1[i]);
    }

    // loading bar
    int bar_width = 40;
    int bar_startx = (80 - bar_width) / 4;
    int bar_y = 6;

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

std::vector<Wordle::colors> Wordle::getColors(const std::string &guess) const
{
    // list the quantity of each letter present in answer and guess, (e.g. candy has 1 c, 1 a, 1 n, etc.)
    std::unordered_map<char, int> answerLettersCount;
    std::unordered_map<char, int> guessLettersCount;

    for (int x = 0; x < guess.length(); x++)
    {
        answerLettersCount[answer[x]]++;
        guessLettersCount[guess[x]]++;
    }
    std::vector<Wordle::colors> result(guess.length(), white); // declares vector of size guessLength and fills it with white

    
    //  green letters have priority
    for (int k = 0; k < guess.length(); k++)
    {
        if (guess[k] == answer[k])
        {
            result[k] = green;
            answerLettersCount[guess[k]]--;
        }
    }
    for (int j = 0; j < guess.length(); j++)
    {
        // letter not in right position and quantity of letter in guess is less than its quantity in answer
        if (guess[j] != answer[j] && guessLettersCount[guess[j]] != 0 && guessLettersCount[guess[j]] <= answerLettersCount[guess[j]])
        {

            result[j] = yellow;
            guessLettersCount[guess[j]]--;
        }
    }

    return result;
}

void Wordle::endScreen() {
    clear();
    refresh();

    WINDOW *windowTest = newwin(30, 100, 6, 60);


    const char *ascii_art[] = {
       "      _____________,--,",
        "      | | | | | | |/ .-.\\   HANG IN THERE",
        "      |_|_|_|_|_|_/ /   `.      SANTA",
        "       |_|__|__|_; |      \\",
        "       |___|__|_/| |     .'`}`",
        "       |_|__|__/ | |   .'.'`\\",
        "       |__|__|/  ; ;  / /    \\.-\"-.\"",
        "       ||__|_;   \\ \\  ||    /`___. \\",
        "       |_|___/\\  /;.`,\\\\   {_'___.;{",
        "       |__|_/ `;`__|`-.;|  |C` e e`\\",
        "       |___`L  \\__|__|__|  | `'-o-' }",
        "       ||___|\\__)___|__||__|\\   ^  /`\\",
        "       |__|__|__|__|__|_{___}'.__.`\\_.'}",
        "       ||___|__|__|__|__;\\_)-'`\\   {_.-;",
        "       |__|__|__|__|__|/` (`\\__/     '-'",
        "       |_|___|__|__/`      |",
        "------|__|___|__/`         \\-------------------",
        "-.__.-.|___|___;`            |.__.-.__.-.__.-.__",
        "  |     |     ||             |  |     |     |",
        "-' '---' '---' \\             /-' '---' '---' '---",
        "     |     |    '.        .' |     |     |     |",
        "'---' '---' '---' `-===-'`--' '---' '---' '---'",
        "  |     |     |     |     |     |     |     |",
        "-' '---' '---' '---' '---' '---' '---' '---' '---'",
        "     |     |     |     |     |     |     |     |",
        "'---' '---' '---' '---' '---' '---' '---' '---'---'",
        nullptr
        };

        int text_startx = (60 - strlen("hello world")) / 2;

        mvwprintw(windowTest, 1, text_startx - 7, "Thanks for playing!");
        wrefresh(windowTest);

    
        int start_y = 8;  
        for (int i = 0; ascii_art[i] != nullptr; i++) {
            mvwprintw(windowTest, start_y + i, 0, ascii_art[i]);
        }
        wrefresh(windowTest);

        // countdown message
        for (int i = 5; i >= 0; i--) {
            mvwprintw(windowTest, 4, 12, "Closing window in %d seconds...", i);
            wrefresh(windowTest);

            std::this_thread::sleep_for(std::chrono::seconds(1));
            
        }
        werase(windowTest);
        wrefresh(windowTest);
        delwin(windowTest);

        endwin();
}






Wordle::~Wordle()
{
    endwin();
}