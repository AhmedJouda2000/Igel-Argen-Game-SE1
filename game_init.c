/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * This function creates the board for the first time
 *
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]){

    for (int i =0; i< NUM_ROWS; i++){
        for(int j =0; j < NUM_COLUMNS; j++){
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if((i == 0 && j==3) || (i == 1 && j == 6) || (i ==2 && j ==4)
                    || (i == 3 && j ==5) || (i==4 && j==2) || (i==5 && j==7)){
                board[i][j].type = OBSTACLE;
            } else{
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
        }
    }
}


 /*
 * This function creates players for the first time
 *
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[]){

    char* colours[6] = {"RED", "BLU", "GREEN", "YELLOW", "PINK", "ORANGE"};

    int choice;
    int i = 0;
    while (i<6)
    {
      printf("\nPlease enter your name:       If all players have been inputted press Enter\n");
      fgets(players[i].name, 20, stdin);
      //Checks whether a carriage return symbol was provided as input
      if(players[i].name[0] == '\n' && i > 1)
          break;

      while (players[i].name[0] == '\n') {
        printf("Minimum players is 2, please enter name: \n");
        fgets(players[i].name, 20, stdin);
      }

      printf("Please Pick a colour:\n");
      for (size_t j = 0; j < 6; j++)
      {
        printf("%d) %s\n", j+1, colours[j]);
      }
      scanf("%d", &choice);
      getchar();
      choice--;
      players[i].col = choice;
      i++;
    }

    printf("\n****Game Intialized****\n");
    for (size_t z = 0; z < i; z++)
    {
      printf("Player %d: %sColour: ", z+1, players[z].name);
      switch (players[z].col) {
        case(0):
          printf("Red\n\n");
          break;
        case(1):
          printf("Blu\n\n");
          break;
        case(2):
          printf("Green\n\n");
          break;
        case(3):
          printf("Yellow\n\n");
          break;
        case(4):
          printf("Pink\n\n");
          break;
        case(5):
          printf("Orange\n");
          break;
      }
    }
    printf("\nTotal number of Players: %d\n\n", i);
    printf("----------------------------------------------------\n\n");


        return i;
    }
