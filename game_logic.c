/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 *
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */
char print_token(token *t){
    if((*t).col== PINK) return 'P';
    if((*t).col== RED) return 'R';
    if((*t).col== BLU) return 'B';
    if((*t).col== GREEN) return 'G';
    if((*t).col== ORANGE) return 'O';
    if((*t).col== YELLOW) return 'Y';
    return '\0';
}

/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]){
    printf("                THE BOARD\n");
    for(int i =0; i < NUM_ROWS; i++){

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i);
        char c = '\0' ;
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++){
            if(board[i][j].stack != NULL){
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else{
                //c is assigned 'X' if the square represents an obstacle
                if(board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else c = ' ';
            }
            printf("| %c ", c);
        }
        printf ("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     0   1   2   3   4   5   6   7   8\n");
}

void printLine(){
  printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    // TO BE IMPLEMENTED
    int minNumOfTokens = 0;
    int selectedSquare = 0;

    for (size_t z = 0; z < 6; z++) {
      board[z][0].numTokens = 0;
    }

    for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < numPlayers; j++)
      {

        printf("Player %d (%s) please select a square\n", j, players[j].name);
        scanf("%d", &selectedSquare);

        while (minNumOfTokens != board[selectedSquare][0].numTokens) {
          printf("TRY AGAIN: MUST BE SQAURE WITH LEAST TOKENS\n");
          printf("Player %d (%s) please select a square\n", j, players[j].name);
          scanf("%d", &selectedSquare);
        }


        if (minNumOfTokens == board[selectedSquare][0].numTokens)
        {

            board[selectedSquare][0].stack = (token *) malloc(sizeof(token));
            board[selectedSquare][0].stack->col = players[j].col;
            board[selectedSquare][0].numTokens++;


        }
        if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
        {
          minNumOfTokens++;
          printf("\t\tminim no. tokens %d\n", minNumOfTokens);
        }

      }
    }

    printf("\n\n%d\n\n%d", board[0][0].numTokens, board[1][0].numTokens);
}


/*
 * Place tokens in the first column of the board
 *
 if (players[j].col != board[selectedSquare][0].stack->col)
 {
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //TO BE IMPLEMENTED
}
