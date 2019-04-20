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

  //
  // Function for placing token at the start of the game
  //
  void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
  {
      int minNumOfTokens = 0;
      int selectedSquare = 0;

      int j=0;
      for (size_t z = 0; z < 6; z++) {
        board[z][0].numTokens = 0;
      }

      for (size_t i = 0; i < 4; i++)
      {
        for (size_t j = 0; j < numPlayers; j++)
        {

          printf("Player %d - %sPlease select a square (Row 0 - 5)\n", j+1, players[j].name);
          scanf("%d", &selectedSquare);

          while (minNumOfTokens != board[selectedSquare][0].numTokens) {
            printf("TRY AGAIN: MUST BE SQAURE WITH LEAST TOKENS\n");
            printf("Player %d %sPlease select a square\n", j+1, players[j].name);
            scanf("%d", &selectedSquare);
          }

          //Checks if user is blocking their own token in stack, only gives 1 chance
          while (board[selectedSquare][0].numTokens > 0 && board[selectedSquare][0].stack->col == players[j].col) {
            printf("\nError: can't place on your own colour\n");
            printf("Player %d %sPlease select a square\n", j+1, players[j].name);
            scanf("%d", &selectedSquare);
          }

          if (minNumOfTokens == board[selectedSquare][0].numTokens )
          {
              board[selectedSquare][0].numTokens++;
              push(&board[selectedSquare][0].stack, players[j].col);
          }

          if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
          {
            minNumOfTokens++;
            printf("\t\tminim no. tokens %d\n", minNumOfTokens);
          }
          system("cls");
          print_board(board);
      }
    }

  }

  //
  // Function to check if someone has one
  //
   int check_win(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
     for (size_t i = 0; i < numPlayers; i++) {
       if (players[i].numTokensLastCol == 3) {
         printf("**********\nTHE WINNER IS %s**********\n", players[i].name);
         return 0;
       }
       else return 1;
     }

   }

   //
   // Function to handle obstacle squares
   //
    int on_obstacle_square(square board[NUM_ROWS][NUM_COLUMNS], int dice, int j) {
      int canProceed = 1;

      if (board[dice][j].type == OBSTACLE) {
        for (size_t i=0;i<j;i++) {
          for (size_t k=0;k<=6;k++){
            if (board[k][i].stack != NULL) {
              canProceed = 0;
            }
          }
        }
      }

      return canProceed;
    }

  //
  // Function where most game actions take place
  //
  void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int j, choice;
    char direction;

    for (size_t c = 0; c < numPlayers; c++) {
      players[c].numTokensLastCol = 0;
    }


    while (check_win(board, players, numPlayers)) {
      for (size_t i=0; i<numPlayers; i++) {
        srand(time(NULL));    //roll a dice here
        int dice = rand()%6;

        printf("\nTurn: %sDice rolled: %d\nAt the end of your turn a token in row %d will be moved\n",
         players[i].name, dice, dice);

         printf("\nDo you wish to move a token? 1 for Yes\n");
         scanf("%d", &choice);


         if (choice == 1) {
          printf("Choose a square with your token in it [y x]\n");
          int chooseToken, chooseToken2;
          scanf("%d %d", &chooseToken, &chooseToken2);
          getchar();

          while (board[chooseToken][chooseToken2].stack == NULL || board[chooseToken][chooseToken2].stack->col != players[i].col) {
            printf("\nMust Select a square with your token\n");
            scanf("%d %d", &chooseToken, &chooseToken2);
            getchar();
            continue;
          }
            switch (chooseToken) {
              case(0):
              //if top row picked token MUST move down
              if(on_obstacle_square(board, 0, chooseToken2)) {
                push(&board[1][chooseToken2].stack, board[0][chooseToken2].stack->col);
                pop(&board[0][chooseToken2].stack);
              }
              else {
                printf("\n[0][%d] is an obstacle square", chooseToken, chooseToken2);
              }
              break;

              case (5):   //if bottom row picked token MUST move up
              if(on_obstacle_square(board, 5, chooseToken2)) {
                push(&board[4][chooseToken2].stack, board[5][chooseToken2].stack->col);
                pop(&board[5][chooseToken2].stack);
              }
              else {
                printf("\n[5][%d] is an obstacle square", chooseToken, chooseToken2);
              }
              break;

              default:  //else let user pick which direction to move
                printf("What direction to move? (u) or (d)?\n");
                scanf("%c", &direction);
                getchar();

                if (direction == 'u' || direction == 'U') {
                  if(on_obstacle_square(board, chooseToken, chooseToken2)) {
                    push(&board[chooseToken-1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                    pop(&board[chooseToken][chooseToken2].stack);
                  }
                  else {
                    printf("\n[%d][%d] is an obstacle square", chooseToken, chooseToken2);
                  }
                }
                else if (direction == 'd' || direction == 'D') {
                  if(on_obstacle_square(board, chooseToken, chooseToken2)) {
                    push(&board[chooseToken+1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                    pop(&board[chooseToken][chooseToken2].stack);
                  }
                  else {
                    printf("\n[%d][%d] is an obstacle square", chooseToken, chooseToken2);
                  }
                }
                else {
                  printf("Error, not a valid direction\n");
                }
               }
             }

          print_board(board);
          printf("\nYou can move tokens in squares:\n");
          for (size_t k=0;k<9;k++) {
              if (board[dice][k].stack != NULL) {
                printf("[%d][%d]\n",dice, k);
              }
          }

          for (size_t r = 0; r < 8; r++) {
            if (board[dice][r].stack != NULL) {
              printf("Enter the column of the square you want to move:");
              scanf("%d", &j);

              while (board[dice][j].stack == NULL || j >= 8) {
                printf("Invalid input\nChoose: ");
                scanf("%d", &j);
              }

                if(on_obstacle_square(board, dice, j)) {
                // Move one token 1 column right
                push(&board[dice][j+1].stack, board[dice][j].stack->col);
                pop(&board[dice][j].stack);

                print_board(board);
                printf("\nToken was moved to [%d][%d]\n", dice, j+1);

                if ((j+1) == 8)
                {
                  for (size_t w = 0; w < numPlayers; w++) {
                    if (board[dice][j+1].stack->col == players[w].col) {
                      players[w].numTokensLastCol++;
                      printf("\n\nUPDATE: %sTokens in last column = %d\n\n", players[w].name, players[w].numTokensLastCol);
                    }
                  }
                }
              }
              else {
                printf("\nSquare [%d][%d] is an obstacle! No token moved", dice, j);
              }
              break;
            }
          }


        }
      }
    }
