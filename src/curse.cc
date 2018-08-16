/**
 * @file    curse.cc
 * @author  Pekka Koivuniemi
 * @date    20 Jul 2018
 * @version 0.1
 * @brief   Implementation of curses graphical user interface of the Tic-tac-toe game.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

#include "curse.h"

/*********  Game board window  *********/

/*
 * To convert some graphical characters to chtype.
 * Needed for mvaddch().
 */
const char HLINE = '-';
const char VLINE = '|';
const char CROSS = '+';
const char SPACE = ' ';

// Cell sizes, one border character included
const size_t SIZE_Y = 2;
const size_t SIZE_X = 4;
// Number of cells
const size_t CELLS_Y = 3;
const size_t CELLS_X = 3;
const size_t CELLS   = CELLS_Y * CELLS_X ;

const size_t GROWS = CELLS_Y * SIZE_Y - 1;
const size_t GCOLS = CELLS_X * SIZE_X - 1;
const char grid[GROWS][GCOLS+1] = {
//   01234567890
    "   |   |   ", //0
    "---+---+---", //1
    "   |   |   ", //2
    "---+---+---", //3
    "   |   |   ", //4
};


// These ones maybe not needed in final implementation
const char X = 'X';
const char O = 'O';
const char F = ' ';

const size_t GRID_WIN_Y = 3;
// Calculate startX-coord grid window
// We use #define as it can change at run time by screen resize
// Let its x-center be at 1/2 of the width of the screen
#define GRID_WIN_X (COLS/2 - GCOLS/2)

/*************  Users' windows  *************/

const size_t USER1_WIN_Y = GRID_WIN_Y + GROWS + 1;
const size_t USER2_WIN_Y = GRID_WIN_Y + GROWS + 1;
const size_t USER_WIN_LEN_Y = 4;
const size_t USER_WIN_LEN_X = 10;

/*************  Draw window  *************/

const size_t DRAW_WIN_Y = USER1_WIN_Y + 1;
const size_t DRAW_WIN_LEN_Y = 3;
const size_t DRAW_WIN_LEN_X = 5;
#define DRAW_WIN_X (COLS/2 - DRAW_WIN_LEN_X/2)

// *** Calculate startX-coord of each player's window ***
// We use #define as it can change at run time by screen resize
// Player1: Let its right side be at 8 chars from draw window's left side 
#define USER1_WIN_X (DRAW_WIN_X - 8 - USER_WIN_LEN_X)
// Player2: Let its left side be at 8 chars from draw window's right side 
#define USER2_WIN_X (DRAW_WIN_X + DRAW_WIN_LEN_X + 8)


// Color pairs
const int COLOR_NORMAL      = 1;
const int COLOR_HIGHLIGHT   = 2;
const int COLOR_QUERY       = 3;
const int COLOR_WIN         = 4;
const int COLOR_DRAW        = 5;
const int COLOR_LOSE        = 6;


// Area for some debug info
const size_t NUM_INFO_LINES = 3;
#define INFO_Y LINES - NUM_INFO_LINES

/*************  Query window  *************/
// ...
/***/

/*** non-class member functions ***/

void sleepMilliseconds(int ms);
void purgeInput(void);
void initColors(void);

/*************************************************************************/

/*
 * Initialize curses mode 
 */ 
void Curse::initCurse(void)
{
    initscr();          // Start curses mode
    start_color();      // Start the color functionality
    cbreak();           // Line buffering disabled
    keypad(stdscr, TRUE); // Needed?
    noecho();           // echo off

    //showColors();

    initColors();
    attron(COLOR_PAIR(1));

    createSubWindows();
    purgeInput();
}

/**
 * End curses mode, i.e. restore normal terminal
 */
void Curse::endCurse(void)
{
    endwin();
}

/**
 * A help funtion to show colors on the screen.
 * Just to see how each color look like.
 * Not used in final version.
 */
#if 0
void showColors(void)
{
    const char *cname[] = {
        "Black      ",
        "Red        ",
        "Green      ",
        "Yellow     ",
        "Blue       ",
        "Magenta    ",
        "Cyan       ",
        "White      ",
    };
    
    init_pair(1, COLOR_BLACK,   COLOR_BLACK);
    init_pair(2, COLOR_RED,     COLOR_BLACK);
    init_pair(3, COLOR_GREEN,   COLOR_BLACK);
    init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(5, COLOR_BLUE,    COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(7, COLOR_CYAN,    COLOR_BLACK);
    init_pair(8, COLOR_WHITE,   COLOR_BLACK);

    for (size_t colo = 0; colo < 8; colo++) {
        attroff(A_REVERSE | A_BOLD);
        attron(COLOR_PAIR(colo+1) | A_NORMAL);
        mvprintw(colo, 0, "%lu: ", colo);
        for (size_t bold = 0; bold < 2; bold++) {
            if (bold) 
                attron(A_BOLD);
            printw(cname[colo]);
            attroff(A_NORMAL);
            attron(A_REVERSE);
            //attron(COLOR_PAIR(colo+1) | A_REVERSE);
            printw(cname[colo]);
            attroff(A_REVERSE | A_BOLD);
            refresh();
        }
        attroff(COLOR_PAIR(colo+1));
    }
    //refresh();
    getch();
}
#endif
/**
 * Initialize color pairs
 */
void initColors(void)
{
    init_pair(COLOR_NORMAL,    COLOR_CYAN,  COLOR_BLACK);
    init_pair(COLOR_HIGHLIGHT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_QUERY,     COLOR_BLUE,  COLOR_BLACK);
    init_pair(COLOR_WIN,       COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_DRAW,      COLOR_BLACK, COLOR_YELLOW);
    init_pair(COLOR_LOSE,      COLOR_BLACK, COLOR_RED);
}

/**
 * Create a new window, does not show up anything on the screen.
 * @param ref to win subwindowfilled by the the created window information
 * @param starty,startx upper left corner coordinates of the window
 * @param leny,lenx height and width of the window
 */
void Curse::createWindow(subWin_t& win, int starty, int startx, int leny, int lenx)
{
    win.starty = starty;
    win.startx = startx;
    win.leny   = leny;
    win.lenx   = lenx;
    win.win    = newwin(win.leny, win.lenx, win.starty, win.startx);
    wattron(win.win, COLOR_PAIR(COLOR_NORMAL));
}

/**
 * Create subwindows for game grid, players and draws.  
 * Does not show up anything on the screen.
 */
void Curse::createSubWindows(void)
{
    // Grid window
    createWindow(gridWin.subWin, GRID_WIN_Y, GRID_WIN_X, GROWS, GCOLS);

    // Users' windows
    for (size_t i = 0; i < NUM_PLAYERS; i++) {
        createWindow(userWin[i].subWin, 
                     i ? USER2_WIN_Y : USER1_WIN_Y,
                     i ? USER2_WIN_X : USER1_WIN_X,
                     USER_WIN_LEN_Y, USER_WIN_LEN_X);
    }

    // Draw window
    createWindow(drawWin.subWin, 
                 DRAW_WIN_Y, DRAW_WIN_X, 
                 DRAW_WIN_LEN_Y, DRAW_WIN_LEN_X);
}

/**
 * Display user information (name, score, ..) on the screen.
 * @param uw user information structure
 */
void Curse::showUserWindow(userWin_t& uw, const char* infoText = NULL)
{
    mvwaddnstr(uw.subWin.win, 0, 0, uw.playerName.c_str(), uw.subWin.lenx);
    mvwprintw(uw.subWin.win, 1, 0, "Playing %c", uw.symbol);
    mvwprintw(uw.subWin.win, 2, 0, "Score: %lu  ", uw.score);
    if (infoText)
        mvwaddnstr(uw.subWin.win, 3, 0, infoText, uw.subWin.lenx);
    wrefresh(uw.subWin.win);
}

/**
 * Display draws (ties) on the screen.
 */
void Curse::showDrawWindow(const char* infoText = NULL)
{
    mvwaddnstr(drawWin.subWin.win, 0, 0, "Draws", drawWin.subWin.lenx);
    mvwprintw( drawWin.subWin.win, 1, 0, "%lu  ", drawWin.score);
    if (infoText)
        mvwaddnstr(drawWin.subWin.win, 2, 0, infoText, drawWin.subWin.lenx);
    wrefresh(drawWin.subWin.win);
}

/**
 * Convert char to chtype.
 * Used to draw vertical and horzontal lines more graphically.
 * @param c char to convert
 * @return converted character if a graphical char,
 *         other wise given char is returned
 */
chtype char2chtype(char c)
{
    chtype ch;
    ch = c == HLINE ? ACS_HLINE :
         c == VLINE ? ACS_VLINE :
         c == CROSS ? ACS_PLUS  :
         c;
    
    return ch;
}

/**
 * Display grid on the screen.
 */
void Curse::showGrid(void) 
{
    for (size_t y = 0; y < GROWS; y++)
        for (size_t x = 0; x < GCOLS; x++) {
            char c = grid[y][x];
            mvwaddch(gridWin.subWin.win, y, x, char2chtype(c)); 
        }
        
    wrefresh(gridWin.subWin.win);
}

/**
 * Convert absolute screen coordinates to cell index on game board
 * @param y absolute screen row coordinate
 * @param x absolute screen column coordinate
 * @return on success return cell on game board (0-8)
 *         at a non-cell location return < 0
 */
int Curse::getCellNumber(int y, int x)
{
    int gy = y - gridWin.subWin.starty;
    int gx = x - gridWin.subWin.startx;
    
    // Off-window?
    if (gy < 0 || gy >= gridWin.subWin.leny ||
        gx < 0 || gx >= gridWin.subWin.lenx)
        return -1;
    
    // At grid border?
    if (((gy + 1) % SIZE_Y == 0) ||
        ((gx + 1) % SIZE_X == 0))
        return -1;
    
    int celly = gy / SIZE_Y;
    int cellx = gx / SIZE_X;
    
    return celly * CELLS_X + cellx;
}

/**
 * Convert game board cell number to grid coordinates
 * @param cell cell number (0-8) on the game board
 * @param winy returned row number at game grid window
 * @param winx returned column number at game grid window
 */
void Curse::getGridCoords(int cell, int& winy, int& winx)
{
    assert(cell >= 0 && cell < (int)CELLS);

    winy = cell / CELLS_X * SIZE_Y;
    winx = (cell % CELLS_X) * SIZE_X + 1;
}


/**
 * Get cell selection on the game board done by the user with mouse.
 * @return selected cell number [0,8]
 *         or 'Q' or 'q' to quit
 */
int Curse::getMove(void)
{

    int move;
    bool done = false;
    while(!done) {
        MEVENT event;
        int ch = wgetch(stdscr);
        switch(ch) {
            case KEY_MOUSE:
                if ((getmouse(&event) == OK) && 
                    (event.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED))) {
                    // User made a mouse click
                    done = ((move = getCellNumber(event.y, event.x)) >= 0);
                }
                break;
            default: // Keyboard
                move = ch;
                if (move >= '1' && move <= '9') {
                    move -= '1'; // -> binary [0,8]
                    done = true;
                } 
                else if (move == 'q' || move == 'Q') {
                    done = true;
                }
                break;
        }
        //mvprintw(INFO_Y, 1, "bstate=0x%x ch=%d    ", event.bstate, ch);
    }
    return move;
}
                          
/**
 * Set attribute (e.g. color, inverse video) of given cells.
 * @param cells vector of cell numbers [0,8] on the game board
 * @param colorPair color pair to set for the given cells
 */
void Curse::setCellsColor(std::vector<int>& cells, int colorPair)
{
    for (auto cell : cells) {
        int winy, winx;
        getGridCoords(cell, winy, winx);
        mvwchgat(gridWin.subWin.win, winy, winx-1, 3, A_NORMAL, colorPair, NULL);
    }
    wrefresh(gridWin.subWin.win);
}

/**
 * Update game board on the screen according to the given game board content.
 * @param board symbols on the game board
 */ 
void Curse::updateBoard(const boardMtx__t& newBoard)
{
    std::vector<int> addedCells;
    for (int cell = 0; cell < (int)CELLS; cell++) {
        if (savedBoard[cell] != newBoard[cell]) {
            savedBoard[cell] =  newBoard[cell];
            int winy, winx;
            getGridCoords(cell, winy, winx);
            mvwaddch(gridWin.subWin.win, winy, winx, newBoard[cell]);
            if (newBoard[cell] != F)
                addedCells.push_back(cell);
        }
    }

    // Highlight the added symbols (if any) for a moment
    if (addedCells.size()) {
        setCellsColor(addedCells, COLOR_HIGHLIGHT);
        sleepMilliseconds(500);
        setCellsColor(addedCells, COLOR_NORMAL);
        sleepMilliseconds(100);
    } else {
        wrefresh(gridWin.subWin.win);
    }
}

/**
 * Highlight the winning line on the game board
 * @param wl cell indicies [0,8] of the winning line
 */
void Curse::showWinningLine(winLine__t& wl)
{
    std::vector<int> vWinLine(wl.begin(), wl.end());
    setCellsColor(vWinLine, COLOR_HIGHLIGHT);
}

/**
 * Ask player's name from the user.
 * @param playerNumber order number of the player [1, NUM_PLAYERS]
 */
std::string Curse::askPlayerName(int playerNumber) 
{
    assert(playerNumber >= 1 && playerNumber <= NUM_PLAYERS);

    const size_t maxLen = USER_WIN_LEN_X;
    char askBuf[maxLen + 1];
    const char queryTxt[] = "Enter player %d name: ";

    curs_set(1);
    echo();
    color_set(COLOR_QUERY, NULL);

    if (playerNumber == 1)
        mvprintw(5, 0, "");
    
    for (askBuf[0] = 0; strlen(askBuf) == 0;) {
        printw(queryTxt, playerNumber);
        getnstr(askBuf, maxLen);
    }

    color_set(COLOR_NORMAL, NULL);
    noecho();
    curs_set(0);

    userWin[playerNumber -1].symbol     = playerNumber == 1 ? 'X' : 'O';
    userWin[playerNumber -1].score      = 0;
    userWin[playerNumber -1].playerName = askBuf;
    drawWin.score = 0;
    return userWin[playerNumber - 1].playerName;
}

/** 
 * Ask from the user if the player is computer/machine or human.
 * @param playerNumber the order number of the player
 * @return true:  player is computer/machine. 
 *         false: player is human
 */
bool Curse::askIfMachine(int playerNumber)
{
    assert(playerNumber >= 1 && playerNumber <= NUM_PLAYERS);

    char ch = 0;
    const char queryTxt[] = "Human or Machine (H/M): ";

    curs_set(1);
    echo();
    color_set(COLOR_QUERY, NULL);

    while(ch != 'H' && ch != 'M') {
        printw(queryTxt);
        ch = toupper(getch());
        printw("\n");
    }

    color_set(COLOR_NORMAL, NULL);
    noecho();
    curs_set(0);

    userWin[playerNumber - 1].isMachine = (ch == 'M');
    return userWin[playerNumber - 1].isMachine;
}

/** 
 * Get the order number of the player who plays the given symbol.
 * @param symbol 'X' or 'O'
 * @return the player number playing the given symbol
 */
int Curse::playerNumberBySymbol(char symbol)
{
    int playerNumber;

    for (playerNumber = 0; playerNumber < NUM_PLAYERS; playerNumber++)
        if (userWin[playerNumber].symbol == symbol)
            break;

    assert(playerNumber < NUM_PLAYERS);

    return playerNumber;
}

/**
 * Set next player's turn (can be human or machine)
 * Unhighlight the previous player's window if any
 * Higlight the next player's window
 */
void Curse::setTurn(char symbol)
{
    auto nextTurn = playerNumberBySymbol(symbol);
    if (turn >= 0 && turn != nextTurn) {
        wattron(userWin[turn].subWin.win, COLOR_PAIR(COLOR_NORMAL));
        showUserWindow(userWin[turn]);
    }
    turn = nextTurn;
    wattron(userWin[turn].subWin.win, COLOR_PAIR(COLOR_HIGHLIGHT));
    showUserWindow(userWin[turn]);
}

/** 
 * Ask from the user if they want to play again.
 */
bool Curse::askToPlayAgain(void)
{
    char ch = 0;
    const char queryTxt[] = "Play again (Y/N): ";

    curs_set(1);
    echo();
    color_set(COLOR_QUERY, NULL);

    while(ch != 'Y' && ch != 'N') {
        mvprintw(3, 0, queryTxt);
        ch = toupper(getch());
    }

    color_set(COLOR_NORMAL, NULL);
    noecho();
    curs_set(0);

    return (ch == 'Y');
}

/**
 * Start to get mouse events
 */
void setMouseOn()
{
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    //printf("\033[?1003h\n"); // Start reporting mouse movement events
}

/**
 * Stop to get mouse events
 */
void setMouseOff()
{
    mousemask(0, NULL);
    //printf("\033[?1003l\n"); // Stop reporting mouse movement events
}

/**
 * Clear the screen and internal game board.
 */
void Curse::clear(void)
{
    erase();
    refresh();

    gridVisible = false;
    std::fill(savedBoard.begin(), savedBoard.end(), ' ');

    setMouseOff();
    mouseIsOn = false;

    if (turn >= 0) {
        wattron(userWin[turn].subWin.win, COLOR_PAIR(COLOR_NORMAL));
        turn = -1;
    }
    wattron(drawWin.subWin.win, COLOR_PAIR(COLOR_NORMAL));
}

/**
 * Display the game board on the screen.
 */
void Curse::showBoard(const boardMtx__t& pm) 
{
    if (!gridVisible) {
        showGrid();
        gridVisible = true;
    }

    updateBoard(pm);

    if (!mouseIsOn) {
        setMouseOn();
        mouseIsOn = true;
    }

}

/**
 * Display scores on the screen.
 */
void Curse::showScores(const std::string& name1, int score1, int draws, const std::string& name2, int score2)
{
    size_t score[NUM_PLAYERS] = {(size_t)score1, (size_t)score2};
    for (int i = 0; i < NUM_PLAYERS; i++) {
        userWin[i].score  = score[i];
        showUserWindow(userWin[i]);
    }

    drawWin.score  = (size_t)draws;
    showDrawWindow();
}

/**
 * Display game result (winner or draw, winning line).
 */
void Curse::showGameResult(winLine__t& winLine)
{
    if (winLine[0] >= 0) {

        // we have a winner
        char symbol = savedBoard[winLine[0]];
        auto winner = playerNumberBySymbol(symbol);
        if (turn != winner) {
            wattron(userWin[turn].subWin.win, COLOR_PAIR(COLOR_NORMAL));
            showUserWindow(userWin[turn]);
        }
        wattron(userWin[winner].subWin.win, COLOR_PAIR(COLOR_HIGHLIGHT));
        showUserWindow(userWin[winner], "**WINNER**");

        showWinningLine(winLine);

    } else { 

        // no winner but draw
        wattron(userWin[turn].subWin.win, COLOR_PAIR(COLOR_NORMAL));
        showUserWindow(userWin[turn]);
        wattron(drawWin.subWin.win, COLOR_PAIR(COLOR_HIGHLIGHT));
        showDrawWindow("*TIE*");
    }

}

/**
 * Ask for an user interaction to start a new game.
 */
bool Curse::askReadyForNewGame()
{
    purgeInput();
    char answer = getch();
    if (answer == '0' || toupper(answer) == 'Q')
        return false;

    return true;
}

/**
 * Stop program execution for a while
 * @param ms delay time in milliseconds
 */
void sleepMilliseconds(int ms)
{
    napms(ms);
}

/**
 * 'Eat' everything (garbage) away possibly in standard input.
 */
void purgeInput()
{
    halfdelay(1);
    while(getch() != ERR);
    nocbreak();
    cbreak();
}



