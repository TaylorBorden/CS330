#include <ncurses.h>
#include <stdlib.h>  /* for malloc, exit() */
#include <unistd.h>  /* for sleep, EOF */
#include <string.h>  /* for strcmp(), strcat()  */
#include "sok_header.h"
// compile this with ncurses linked:
// and link static file
// gcc -Wall -g cs330_sokoban_code.c -L. -lsok_helper_vulcan -o cs330_sokoban -lncurses

/* ======= TO DO ======= */
/* 
- compile and run to ensure everything is working correctly
- write validMove() function
- write movePlayer() function
- test
*/

// Note: in starPusherLevels, largest map is 20 rows x 32 columns
// Note: to dereference a value: *((map + newPlayerY*MAP_COLS) + newPlayerX)

/* some variables we'll use in the game */

    /* these are declared 'extern' in the header since they're used
    in the library and in this c file */
        // these need to match the map (in case you change maps.txt)
        int MAP_COLS = 10;
        int MAP_ROWS = 10;
        // dX and dY are helpers for movement: up, right, down, left
        int dX[4] = {0,1,0,-1};
        int dY[4] = {-1,0,1,0};
        int numStarsSolved = 0;  // to represent the number of stars in the correct spot
        int NUM_STEPS = 0;      // to keep score

    /* the windows */
    WINDOW *title_bar;
    WINDOW *main_win;
    WINDOW *score_win;
    int WIN_OFFSET_X = 5;  // offset the upper left of the windows
    int WIN_OFFSET_Y = 0;
    int WIN_WIDTH = 25;
    int WIN_TITLE_HEIGHT = 3;
    int WIN_MAIN_HEIGHT = 22;    // can adjust this if it doesn't fit on screen
    int WIN_SCORE_HEIGHT = 4;
/*
Map values where 0=empty square, 1=wall, 2=player, 3=star, 4=goal square, 5=star on goal, 6 =player on goal
    Note: the following map is just a reference
    The real map is read in from the maps.txt file
       via the read_in_maps() function
int secondMap[10*10] = {
    1,1,1,1,1,1,1,1,1,1,
    1,0,2,0,1,1,0,0,0,1,
    1,0,3,0,0,0,0,0,0,1,
    1,0,4,0,0,0,0,0,0,1,
    1,0,0,0,0,3,0,4,0,1,
    1,0,0,0,0,0,0,0,0,1,
    0,1,1,0,0,0,0,0,0,1,
    1,1,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1};
*/


/* draw the screen, given the map, number of rows, and number of columns */
int drawScreen(int rows, int cols, int *map){
    int i = 0;
    int j = 0;
    int windowI = i + 1;
    int windowJ = j + 1;
    for(i=0; i<MAP_ROWS; i++){
        for(j = 0; j<MAP_COLS; j++){
            windowI = i + 1;  // adding one gets the map inside the border
            windowJ = j + 1;
            int thisSquare = *((map + i*rows) + j);  // this works because this is really a 1D array in memory
            if (thisSquare == 1){
                mvwprintw(main_win, windowI,windowJ,"%c", '#');
            } else if (thisSquare == 2){
                attron(A_BOLD);  // turn on bold
                attron(COLOR_PAIR(2));  // turn on color previously defined for the player
                mvwprintw(main_win,windowI,windowJ,"%c", 'P');
                mvwchgat(main_win,windowI,windowJ,1,A_BOLD,2,NULL);
                attroff(A_BOLD);  // turn off bold
                attroff(COLOR_PAIR(2));  // turn off color previously defined
            } else if (thisSquare == 3){
                attron(COLOR_PAIR(3));  // turn on color previously defined for the star
                mvwprintw(main_win,windowI,windowJ,"%c", '$');
                mvwchgat(main_win,windowI,windowJ,1,A_BOLD,3,NULL);
                attroff(COLOR_PAIR(3));
            } else if (thisSquare == 4){
                mvwprintw(main_win,windowI,windowJ,"%c", 'O');
            } else if (thisSquare == 5){
                attron(COLOR_PAIR(5));
                mvwprintw(main_win,windowI,windowJ,"%c", '$');
                mvwchgat(main_win,windowI,windowJ,1,A_BOLD,5,NULL);
                attroff(COLOR_PAIR(5));
            } else if (thisSquare == 6){
                attron(A_BOLD);  // turn on bold
                attron(COLOR_PAIR(2));  // turn on color previously defined for the player
                mvwprintw(main_win,windowI,windowJ,"%c", 'P');
                mvwchgat(main_win,windowI,windowJ,1,A_BOLD,2,NULL);
                attroff(A_BOLD);  // turn off bold
                attroff(COLOR_PAIR(2));  // turn off color previously defined
            } else {
                attron(COLOR_PAIR(4));
                mvwprintw(main_win,windowI,windowJ,"%c", '.');
                mvwchgat(main_win,windowI,windowJ,1,0,4,NULL);
                attroff(COLOR_PAIR(4));
            }
        }  // end for j
    } // end for i
    //refresh();
    wrefresh(main_win);
    return 0;
}  // end drawScreen

/* ========== TO DO ========== */
/* create the two functions: validMove() and movePlayer() */




//start of valid move

/*
    this function checks whether a move requested by the player is valid based
    on the game's rules, map boundaries, walls, and player interaction with thr stars on the grid.
    it returns 1 for a valid move and 0 for an invalid one.
*/
int validMove(int direction, Player *p, int *map) {
    // Calculate new player position after move
    int newPlayerX = p->x + dX[direction];
    int newPlayerY = p->y + dY[direction];

    //Check if the move is out of bounds
    if (newPlayerX < 0 || newPlayerX >= MAP_COLS || newPlayerY < 0 || newPlayerY >= MAP_ROWS) {
        return 0; 
    }

    //Calculate the position after the move for the square in front of the player
    int nextSquareX = newPlayerX + dX[direction];
    int nextSquareY = newPlayerY + dY[direction];

    //Check if the next square is out of bounds
    if (nextSquareX < 0 || nextSquareX >= MAP_COLS || nextSquareY < 0 || nextSquareY >= MAP_ROWS) {
        return 0; 
    }

    int thisSquare = *((map + newPlayerY * MAP_COLS) + newPlayerX);
    int nextSquare = *((map + nextSquareY * MAP_COLS) + nextSquareX);

    //Check if the player is trying to move into a wall
    if (thisSquare == 1) {
        return 0; 
    }

    //Check if the player is trying to push a star
    if (thisSquare == 3) {
        // Check if the next square is a wall or another star
        if (nextSquare == 1 || nextSquare == 3) {
            return 0; 
        }

        //check if the move is valid for pushing the star
        if (nextSquare == 0 || nextSquare == 4 || nextSquare == 5) {
            return 1; // Valid move
        }
    }

    //Check if the move is valid for the player without interaction with a star
    if (thisSquare == 0 || thisSquare == 4 || thisSquare == 5) {
        return 1; // Valid move
    }

    return 0; // Invalid move by default
}






//start of move player


/*
    This function deals with the movement of the player in the game grid while considering the rules specific to each type of square.
    (empty space, goal space, star, etc.), making sure that the moves are valid.
    Also, it keeps track of the number of steps taken and the stars solved based on the movement of the player and the stars within the grid.

*/
void movePlayer(int direction, Player *p, int *map) {
    // Calculate new player position after move
    int newPlayerX = p->x + dX[direction];
    int newPlayerY = p->y + dY[direction];

    // Determine the type of square the player is moving from
    int currentSquare = *((map + p->y * MAP_COLS) + p->x);
    int nextSquare = *((map + newPlayerY * MAP_COLS) + newPlayerX);

    // Update map based on the type of move
    if (currentSquare == 2 || currentSquare == 6) {
        // Player moves from a blank space
        if (nextSquare == 0 || nextSquare == 4) {
            // Move player to an empty square or a goal space
            *((map + newPlayerY * MAP_COLS) + newPlayerX) = (currentSquare == 2) ? 2 : 6; // Player or Player on Goal
            *((map + p->y * MAP_COLS) + p->x) = (currentSquare == 2) ? 0 : 4; // Empty or Goal square

            // Update player's position
            p->x = newPlayerX;
            p->y = newPlayerY;

            // Increment number of steps
            NUM_STEPS++;
        } else if ((nextSquare == 3 || nextSquare == 5) && validMove(direction, p, map)) {
            // Calculate the position after the move for the square in front of the player
            int nextSquareX = newPlayerX + dX[direction];
            int nextSquareY = newPlayerY + dY[direction];

            if (*((map + nextSquareY * MAP_COLS) + nextSquareX) == 0 || *((map + nextSquareY * MAP_COLS) + nextSquareX) == 4) {
                // Check if the next square after pushing is empty or a goal
                if (*((map + nextSquareY * MAP_COLS) + nextSquareX) == 0) {
                    *((map + nextSquareY * MAP_COLS) + nextSquareX) = (nextSquare == 3) ? 5 : 3; // Star or Star on Goal
                } else {
                    *((map + nextSquareY * MAP_COLS) + nextSquareX) = 5; // Star on Goal
                }

                // Move player to an empty square or a goal space
                *((map + newPlayerY * MAP_COLS) + newPlayerX) = (currentSquare == 2) ? 2 : 6; // Player or Player on Goal
                *((map + p->y * MAP_COLS) + p->x) = (currentSquare == 2) ? 0 : 4; // Empty or Goal square

                // Update player's position
                p->x = newPlayerX;
                p->y = newPlayerY;

                // Increment number of steps
                NUM_STEPS++;

                // If the star was pushed onto a goal, increment the number of stars in the correct spot
                if (*((map + nextSquareY * MAP_COLS) + nextSquareX) == 5) {
                    numStarsSolved++;
                }
            }
        }
    }
}



/* ========== END TO DO FUNCTIONS ========== */


int main(){
    // finish setting up variables
    int numCols = MAP_COLS;
    int numRows = MAP_ROWS;
    int *map = malloc((MAP_ROWS * MAP_COLS) * sizeof(int));

    Player *p = malloc(sizeof(Player));
    //p->x = 2;    // These values are assigned when the map is read in
    //p->y = 1;
    p->prevSquareValue = 0;

    // read in the map
    int numberOfStars = 0;
    read_in_maps(p, map, &numberOfStars);  // calls function to read in the maps file

    /* ======= set-up ncurses (graphics package) ======= */
    /* you don't need to modify this, unless you want to customize the graphics */
        initscr();  // initializes the screen
        raw();      // line buffering disabled
        keypad(stdscr, TRUE);   // allows for special keys like F1, F2, arrow keys
        noecho();               // don't echo() keypresses
        cbreak();               // don't wait for enter
        if(has_colors() == FALSE)
        {	endwin();
            printf("Your terminal does not support color\n");
            exit(1);
        }
        // for colors:
        start_color();          // start the color functionality
        // create some color combinations (ref num, forground color, background color):
        init_pair(2, COLOR_RED, COLOR_BLACK);  // create a new player color combo with red font and black background
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // create a new color combo with red font and black background
        init_pair(4, COLOR_BLUE, COLOR_BLACK); 
        init_pair(5, COLOR_GREEN, COLOR_BLACK);
        // for the three windows
        title_bar = newwin(WIN_TITLE_HEIGHT, WIN_WIDTH, WIN_OFFSET_Y, WIN_OFFSET_X);
        main_win = newwin(WIN_MAIN_HEIGHT, WIN_WIDTH, WIN_OFFSET_Y + WIN_TITLE_HEIGHT, WIN_OFFSET_X);
        score_win = newwin(WIN_SCORE_HEIGHT, WIN_WIDTH, WIN_OFFSET_Y + WIN_TITLE_HEIGHT + WIN_MAIN_HEIGHT, WIN_OFFSET_X);
        // set up the window borders
        wborder(title_bar, '|', '|', '-', '-', '+', '+', '+', '+');  // a border  // was sdrscr
        // order is left side, right side, top side, bottom side, top left (corner), top right (corner), bottom left (corner), bottom right (corner)
        // can also access via their struct, e.g. title_bar->border.ls = '|';
        wborder(main_win, '|', '|', '-', '-', '+', '+', '+', '+');
        wborder(score_win, '|', '|', '-', '-', '+', '+', '+', '+');
        // set up the title bar window
        mvwprintw(title_bar, 1, (WIN_WIDTH-16)/2, "STAR PUSHER GAME");   // prints in win, y, x, string, (16 # chars in string)
        mvwchgat(title_bar,0, 0, -1, A_BOLD, 1, NULL);	
            /* decoder for mvwchgat:
            * First two parameters specify the position at which to start 
            * Third parameter number of characters to update. -1 means till 
            * end of line
            * Forth parameter is the normal attribute you wanted to give 
            * to the charcter
            * Fifth is the color index. It is the index given during init_pair()
            * use 0 if you didn't want color
            * Sixth one is always NULL 
            */
        refresh();
        wrefresh(title_bar);  // refreshes screen to match what's in memory (was refresh() for default win)
        wrefresh(main_win);
        wrefresh(score_win);
    /* ============================== */
    

    /* ======= game loop ======= */
    int keepLooping = 1;
    while(keepLooping){
        // draw the screen
        drawScreen(numRows, numCols, map);
        // draw score screen
        mvwprintw(score_win, 1, 1, "Steps: %d", NUM_STEPS);
        wrefresh(score_win);
        
        // get user input
        int input = getch();  // get user input
        //printw("%d", input);
        int delta = -1;  // -1 not a value. 0=Up, 1=Right. 2=Down, 3-left (see dX, dY values)
        switch(input){
            case KEY_UP:
                delta = 0;
                break;
            case KEY_RIGHT:
                delta = 1;
                break;
            case KEY_DOWN:
                delta = 2;
                break;
            case KEY_LEFT:
                delta = 3;
                break;
            case 113:           // lower case 'q'
            case 81:            // upper case 'Q'
            case 10:            // enter key
                keepLooping = 0;
                break;
        }
  
        /* ======= TODO ======= */





        // if it's a valid move, move player (and star)
         
        if (validMove(delta, p, map)){
            // move player (and star)
            movePlayer(delta, p, map);
        }
        
        

        /* comment this section out and uncomment the section above
          NOTE:  There should be no TA_... in your code
        */
        /*if (TA_validMove(delta, p, map)){
            // move player (and star)
            TA_movePlayer(delta, p, map);
        }*/
        

        /* ======= END TO DO ======= */

        /* check to see if the player won */


       // Check if the player has won




    int coinsWithStars = 0;

    // Check if each coin has a star on it
    for (int i = 0; i < MAP_ROWS * MAP_COLS; i++) {
    // Check if the current element in the map represents a coin with a star
    if (map[i] == 4 || map[i] == 6) {
        coinsWithStars++; // Increment the count of coins with stars
    }
}
    // Check if all coins have stars
    if (coinsWithStars == 3) {
    mvwprintw(score_win, 2, (WIN_WIDTH - 10) / 2, "YOU WIN !!");
    wrefresh(score_win);
    drawScreen(numRows, numCols, map);
    sleep(2);
    keepLooping = 0;
    }

    }
    
    // else keep looping

    endwin();  // deallocate memory and end ncurses
    return 0;
}