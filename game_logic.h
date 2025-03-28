
/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);


/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);


/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
int check_win(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);
int edge_case(square board[NUM_ROWS][NUM_COLUMNS], player players[], int minNumOfTokens, int j);


//temporary declaration of function to check if there's a winner
//Will be used to exit play_game function
int on_obstacle_square(square board[NUM_ROWS][NUM_COLUMNS], int dice, int j);
