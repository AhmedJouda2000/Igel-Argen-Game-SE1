/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


  #include "game_init.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <time.h>

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

      //pointer to the top of the stack
      struct token *top = NULL;
      //pointer to the current element of the stack
      struct token *curr = NULL;

       //
       // function definitions for push/pop to stack
       //

       void push(struct token **top, enum color col){
           struct token *curr = *top;
           *top = malloc(sizeof(token));
           (*top)->col = col;
           (*top)->next = curr;
        }

       void pop(struct token **top){
           struct token *curr = *top;
           if(curr!=NULL){
               *top = curr->next;
               free(curr);
           }
       }


  void printLine(){
    printf("   -------------------------------------\n");
  }

//To test if there are square which have the minNumOfTokens and arent the colour of the current player
int edge_case(square board[NUM_ROWS][NUM_COLUMNS], player players[], int minNumOfTokens, int j)
{
  //loop over all rows in the column 0
  for (size_t z = 0; z < 6; z++)
            {
              //check that if it does have tokens if they are the minNumOfTokens and not the same colour as the current player
              if ((board[z][0].numTokens > 0)&&(board[z][0].numTokens == minNumOfTokens)&&(board[z][0].stack->col != players[j].col))
              {
                return 1;
              }
            }
            return 0;
}






  //
  // Function for placing token at the start of the game
  //
  void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
  {
      int minNumOfTokens = 0; //minimum number of tokens on all the squares in column 0
      int selectedSquare = 0; //square selected in column 0 by the user

      int j=0;  //loop counter

      //intialize all number of tokens in the squares of column 0 to 0 to avoid errors
      for (size_t z = 0; z < 6; z++) {
        board[z][0].numTokens = 0;
      }

      //print board
      print_board(board);


      //This will place all players 4 tokens in column 0, giving each player 4 turns
      //loop 4 times as each player has 4 tokens
      for (size_t i = 0; i < 4; i++)
      {
        //loop depending on the amount of players as they will have a 4 turns each
        for (size_t j = 0; j < numPlayers; j++)
        {

          //prompt the player to select a square and store it
          printf("Player %d - %sPlease select a square (Row 0 - 5)\n", j+1, players[j].name);
          scanf("%d", &selectedSquare);

          //check if the selected square is in the correct range, if not ask for input again
          while (selectedSquare<0 || selectedSquare>5) {
            printf("\nOutisde Range. Try again\n\n");
            printf("Player %d - %sPlease select a square (Row 0 - 5)\n", j+1, players[j].name);
            scanf("%d", &selectedSquare);
          }

          //check if the selected square contains the minNumOfTokens, if not ask for input again
          while (minNumOfTokens != board[selectedSquare][0].numTokens) {
            printf("TRY AGAIN: MUST BE SQAURE WITH LEAST TOKENS\n");
            //printout the squares with the minNumOfTokens for ease
            printf("\nSquares with least number of tokens:\n");
            for (size_t e = 0; e < 6; e++) {
              if (board[e][0].numTokens == minNumOfTokens)
              {
                printf("%d\t", e);
              }
            }
            printf("\nPlayer %d %sPlease select a square\n", j+1, players[j].name);
            scanf("%d", &selectedSquare);
          }

          //check if the edge case applies or not
          //Edge case: if the only column with the minNumOfTokens has the players colour on top
          //if the edge case occurs we skip the following and allow the player to block himself
          if (edge_case(board, players, minNumOfTokens, j))
          {
            //if the edge case doesnt apply
            //Checks if user is blocking their own token in stack, if they do ask for input again
            while (board[selectedSquare][0].numTokens > 0 && board[selectedSquare][0].stack->col == players[j].col) {
              printf("\nError: can't place on your own colour\n");
              printf("Player %d %sPlease select a square\n", j+1, players[j].name);
              scanf("%d", &selectedSquare);
            }
          }



            //stacking the tokens
            if (minNumOfTokens == board[selectedSquare][0].numTokens )
            {
                board[selectedSquare][0].numTokens++;
                push(&board[selectedSquare][0].stack, players[j].col);
            }

            //incrementing the minNumOfTokens
            if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
            {
              minNumOfTokens++;
              printf("\t\tminim no. tokens %d\n", minNumOfTokens);
            }

            //clear screen and print board
            system("cls");
            print_board(board);



      }
    }

  }

  //
  // Function to check if someone has won
  //loops over all the players numTokensLastCol and if it equals 3 then it prints a message and returns 0
   int check_win(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
     for (size_t i = 0; i < numPlayers; i++) {
       if (players[i].numTokensLastCol == 3) {
         printf("**********\nTHE WINNER IS %s**********\n", players[i].name);
         return 0;
       }
     }
      return 1;
   }


   //
   // Function to handle obstacle squares
   //
    int on_obstacle_square(square board[NUM_ROWS][NUM_COLUMNS], int dice, int j) {
      int canProceed = 1;   //by default token can move off of obstacle

      //If token is on an obstacle nested loops checks to see if all tokens behind it in all
      //rows are empty. If yes, the token can move
      if (board[dice][j].type == OBSTACLE) {
        for (size_t i=0;i<j;i++) {
          for (size_t k=0;k<6;k++) {
            if (board[k][i].stack != NULL) {
              canProceed = 0;
            }
          }
        }
      }
      //If the token can move off of the square it is made a normal square
      if (canProceed == 1) {
        board[dice][j].type = NORMAL;
      }
      return canProceed;  //permission to move/not move is returned
    }



  //
  // Function where most game actions take place
  //
  void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    //some variables used throught the function
    int j, choice;
    char direction;

    //To avoid problems initialize all the player's numTokensLastCol to 0 at the start
    for (size_t c = 0; c < numPlayers; c++) {
      players[c].numTokensLastCol = 0;
    }

    //While no one has won keep looping, giving a turn for each player
    while (check_win(board, players, numPlayers)==1) {
      for (size_t i=0; i<numPlayers; i++) {



          srand(time(NULL));    //roll a dice here
          int dice = rand()%6;  //between 0 and 5

          //Display the dice's result and which player turn it is
          printf("\nTurn: %sDice rolled: %d\nAt the end of your turn a token in row %d will be moved\n",
           players[i].name, dice, dice);

           //ask the user if they would like to move up and down and store their answer
           printf("\nDo you wish to move a token up or down (sidestep)? 1 for Yes\n");
           scanf("%d", &choice);

           //if they do want to move up or down enter the following statement
           if (choice == 1) {
             //To avoid bugs intialize the following to -1
             int chooseToken = -1, chooseToken2 = -1;

             //while the user didn't pick a row in the right range to move, keep taking input
             while (chooseToken<0 || chooseToken>5)
             {
               printf("Enter the row (0-5) of the square with your token in it\n");
               scanf("%d", &chooseToken);
               getchar();
             }

            //while the user didn't pick a column in the right range to move, keep taking input
            while (chooseToken2<0 || chooseToken2>8)
            {
              printf("Enter the column (0-8) of the square with your token in it\n");
              scanf("%d", &chooseToken2);
              getchar();
            }

            //while the choosen square is empty OR it contains another player's token display an error and ask for input again
            while (board[chooseToken][chooseToken2].stack == NULL || board[chooseToken][chooseToken2].stack->col != players[i].col) {
              printf("\nMust Select a square with your token\n");

              do {
                printf("Enter the row (0-5) of the square with your token in it\n");
                scanf("%d", &chooseToken);
                getchar();
              } while(chooseToken<0 || chooseToken>5);

              do {
                printf("Enter the column (0-8) of the square with your token in it\n");
                scanf("%d", &chooseToken2);
                getchar();
              } while(chooseToken2<0 || chooseToken2>8);

              continue;
            }

              //if the choosen square is in row 0 or 5 force the move and dont give the user a choice
              switch (chooseToken) {
                case(0):
                //if top row picked token MUST move down as long as its not an obstacle
                if(on_obstacle_square(board, 0, chooseToken2)) {
                  push(&board[1][chooseToken2].stack, board[0][chooseToken2].stack->col);
                  pop(&board[0][chooseToken2].stack);
                }
                else {
                  printf("\n[0][%d] is an obstacle square", chooseToken, chooseToken2);
                }
                break;

                case (5):   //if bottom row picked token MUST move up as long as its not an obstacle
                if(on_obstacle_square(board, 5, chooseToken2)) {
                  push(&board[4][chooseToken2].stack, board[5][chooseToken2].stack->col);
                  pop(&board[5][chooseToken2].stack);
                }
                else {
                  printf("\n[5][%d] is an obstacle square", chooseToken, chooseToken2);
                }
                break;

                default:  //else let user pick which direction to move and store it
                  printf("What direction to move? (u) or (d)?\n");
                  scanf("%c", &direction);
                  getchar();

                  //if the user picked up enter the following statement
                  if (direction == 'u' || direction == 'U')
                  {
                    //push the token into the above square and pop it from the current one as long as its not an obstacle
                    if(on_obstacle_square(board, chooseToken, chooseToken2))
                    {
                      push(&board[chooseToken-1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                      pop(&board[chooseToken][chooseToken2].stack);
                    }
                    else
                    {
                      printf("\n[%d][%d] is an obstacle square", chooseToken, chooseToken2);
                    }
                  }

                  //if the user picked down enter the following statement
                  else if (direction == 'd' || direction == 'D')
                  {
                    //push the token into the below square and pop it from the current one as long as its not an obstacle
                    if(on_obstacle_square(board, chooseToken, chooseToken2))
                    {
                      push(&board[chooseToken+1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                      pop(&board[chooseToken][chooseToken2].stack);
                    }
                    else
                    {
                      printf("\n[%d][%d] is an obstacle square", chooseToken, chooseToken2);
                    }
                  }
                  else {
                    printf("Error, not a valid direction\n");
                  }
                 }
               }

            print_board(board);
            //for the forward movement display the options
            printf("\nYou can move tokens in squares:\n");
            for (size_t k=0;k<9;k++) {
                if (board[dice][k].stack != NULL) {
                  printf("[%d][%d]\n",dice, k);
                }
            }


            for (size_t r = 0; r < 8; r++) {
              if (board[dice][r].stack != NULL) {
                //prompt the user to enter the column of the square to move forward(right) and store it
                printf("Enter the column of the square you want to move:");
                scanf("%d", &j);

                //if the selected square is empty or is in column 8 or greater display an error and take input again
                while (board[dice][j].stack == NULL || j >= 8) {
                  printf("Invalid input\nChoose: ");
                  scanf("%d", &j);
                }

                  //as long as its not an obstacle push it onto the next square and pop it from the current one
                  if(on_obstacle_square(board, dice, j)) {
                  // Move one token 1 column right
                  push(&board[dice][j+1].stack, board[dice][j].stack->col);
                  pop(&board[dice][j].stack);

                  system("cls");
                  print_board(board);
                  printf("\nToken was moved to [%d][%d]\n", dice, j+1);

                  //check if this token was moved to column 8, if it was enter the following statement
                  if ((j+1) == 8)
                  {
                    //find whose token colour this is and increment that player's numTokensLastCol
                    for (size_t w = 0; w < numPlayers; w++) {
                      if (board[dice][j+1].stack->col == players[w].col) {
                        players[w].numTokensLastCol++;
                        printf("\n\nUPDATE: %sTokens in last column = %d\n\n", players[w].name, players[w].numTokensLastCol);
                      }
                    }
                  }
                }
                else {
                  printf("\nSquare [%d][%d] is an obstacle! No token moved\n", dice, j);
                }
                break;
              }
            }



        }
      }
    }
