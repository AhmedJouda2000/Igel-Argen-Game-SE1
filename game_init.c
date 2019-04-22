
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

    //array of pointers to store the colours
    char* colours[6] = {"RED", "BLU", "GREEN", "YELLOW", "PINK", "ORANGE"};
    int colourFlags[6] = {0,0,0,0,0,0};   //flag array for the colours

    int choice; //variable to store the player's colour choice
    int i = 0;  //loop counter for the number of players

    //loop for a maximum of 6 times as the maximum is 6 players
    while (i<6)
    {
      //prompt the user to input his name - enter is pressed if nomore players are there
      printf("\nPlease enter your name:       If all players have been inputted press Enter\n");
      fgets(players[i].name, 20, stdin);  //use fgets
      //Checks whether a carriage return symbol was provided as input and there are atleast 2 players, if true break
      if(players[i].name[0] == '\n' && i > 1)
          break;
      //dont allow a break unless 2 players have been entered
      while (players[i].name[0] == '\n') {
        printf("Minimum players is 2, please enter name: \n");
        fgets(players[i].name, 20, stdin);
      }

      //prompt the user to pick a colour and print out the colours
      printf("Please Pick a colour:\n");
      for (size_t j = 0; j < 6; j++)
      {
        printf("%d) %s\n", j+1, colours[j]);
      }
      scanf("%d", &choice);   //store the user's choice
      getchar();    //getchar to avoid overflow
      choice--;     //decrement choice as colours are numbered 1-6 while colours are indexed 0-5

      //To check if the colour has already been choosen by another player
      //this also checks if the colour is Outside the range
      //in either cases the loop loops till we get an acceptable input
      while (colourFlags[choice] == 1 || (choice<0 || choice>5))
      {
        printf("Colour already chosen or Outside range! Please Try Again:\n");
        scanf("%d", &choice);
        getchar();
        choice--;
      }

      //assign the colour to the player who picked it
      //flag the colour in the flag array
      players[i].col = choice;
      colourFlags[choice] = 1;
      //increment i to move to the next player
      i++;
    }

    //Now the game has been initialized
    printf("\n****Game Intialized****\n");
    //print out all player names and the colour they picked
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
    //print out the total number of players
    printf("\nTotal number of Players: %d\n\n", i);
    printf("----------------------------------------------------\n\n");

        //return the total number of players
        return i;
    }
