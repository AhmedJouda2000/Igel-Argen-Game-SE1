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
      system("cls");
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

      int j=0;
      for (size_t z = 0; z < 6; z++) {
        board[z][0].numTokens = 0;
      }

      for (size_t i = 0; i < 4; i++)
      {
        for (size_t j = 0; j < numPlayers; j++)
        {

          printf("Player %d) %s please select a square\n", j+1, players[j].name);
          scanf("%d", &selectedSquare);

          while (minNumOfTokens != board[selectedSquare][0].numTokens) {
            printf("TRY AGAIN: MUST BE SQAURE WITH LEAST TOKENS\n");
            printf("Player %d) %s please select a square\n", j+1, players[j].name);
            scanf("%d", &selectedSquare);
          }

          //Checks if user is blocking their own token in stack, only gives 1 chance
          if (board[selectedSquare][0].numTokens > 0 && board[selectedSquare][0].stack->col == players[j].col) {
              printf("\nError: can't place on your own colour\n");
                scanf("%d", &selectedSquare);
              }
          else if (minNumOfTokens == board[selectedSquare][0].numTokens )
          {

              //board[selectedSquare][0].stack = (token *) malloc(sizeof(token));
              board[selectedSquare][0].numTokens++;
              push(&board[selectedSquare][0].stack, players[j].col);
          }

          if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
          {
            minNumOfTokens++;
            printf("\t\tminim no. tokens %d\n", minNumOfTokens);
          }
          print_board(board);
      }
    }

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

   int check_win(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers) {
     int over = 0, i;

     for (i=0;i<numPlayers;i++) {
       if (players[i].numTokensLastCol >= 3) {
         over = 1;
         break;
       }
     }
      if (over == 1) {
        print_board(board);
        printLine();
        printf("%s Wins!", players[i].name);
          return -1;
        }
     else {
       return 1;
     }
   }

  void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int j, choice;
    char direction;

    while (check_win(board, players, numPlayers)) {
      for (size_t i=0; i<numPlayers; i++) {
        srand(time(NULL));    //roll a dice here
        int dice = rand()%6;

        printf("\n%s rolled: %d\nAt the end of your turn a token in row %d will be moved\n",
         players[i].name, dice, dice);

         printf("\nDo you wish to move a token? 1 for yes\n");
         scanf("%d", &choice);


         if (choice == 1) {
          printf("Choose a square with your token in it (x,y)\n");
          int chooseToken, chooseToken2;
          scanf("%d %d", &chooseToken, &chooseToken2);
          getchar();

          while (board[chooseToken][chooseToken2].stack->col != players[i].col || board[chooseToken][chooseToken2].stack == NULL) {
            printf("\nCan only select a square with your token\n");
            scanf("%d %d", &chooseToken, &chooseToken2);
            getchar();
            continue;
          }
             switch (chooseToken) {
              case(0):
              //if top row picked token MUST move down
              push(&board[1][chooseToken2].stack, board[0][chooseToken2].stack->col);
              pop(&board[0][chooseToken2].stack);
              break;

              case (5):   //if bottom row picked token MUST move up
              push(&board[4][chooseToken2].stack, board[5][chooseToken2].stack->col);
              pop(&board[5][chooseToken2].stack);
              break;

              default:  //else let user pick which direction to move
                printf("What direction to move? (u) or (d)?\n");
                scanf("%c", &direction);
                getchar();

                if (direction == 'u') {
                  push(&board[chooseToken-1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                  pop(&board[chooseToken][chooseToken2].stack);
                }
                else if (direction == 'd') {
                  push(&board[chooseToken+1][chooseToken2].stack, board[chooseToken][chooseToken2].stack->col);
                  pop(&board[chooseToken][chooseToken2].stack);
                }
                else {
                  printf("Error, not a valid direction\n");
                }
               }
             }

          j=0;
          while (board[dice][j].stack == NULL) {
            j++;    //Loop checks what colum the token to be moved is in
          }

          // Move one token 1 column right
          push(&board[dice][j+1].stack, board[dice][j].stack->col);
          pop(&board[dice][j].stack);

          if (j+1 == 8) {
            for (size_t k=0;k<numPlayers;k++) {
              if (board[dice][8].stack->col == players[k].col) {
                players[k].numTokensLastCol++;
                pop(&board[dice][8]);
              }
            }
          }

          print_board(board);
          printf("\nToken was moved to [%d][%d]\n", dice, j+1);
        }
      }
    }
