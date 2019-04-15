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
       struct token * push(enum color value, struct token *top){
           struct token *curr = top;
           top = malloc(sizeof(token));
           top->col = value;
           top->next = curr;
           return top;
        }

       struct token * pop(struct token *top){
           struct token *curr = top;
           if(curr!=NULL){
               top = curr->next;
               free(curr);
           }
           return top;
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

          printf("Player %d) %s please select a square\n", j, players[j].name);
          scanf("%d", &selectedSquare);

          while (minNumOfTokens != board[selectedSquare][0].numTokens) {
            printf("TRY AGAIN: MUST BE SQAURE WITH LEAST TOKENS\n");
            printf("Player %d) %s please select a square\n", j, players[j].name);
            scanf("%d", &selectedSquare);
          }

          //Checks if user is blocking their own token in stack, only gives 1 chance
          if (board[selectedSquare][0].numTokens > 0 && board[selectedSquare][0].stack->col == players[j].col) {
              printf("\nError: can't place on your own colour\n");
                  scanf("%d", &selectedSquare);
              }
          else if (minNumOfTokens == board[selectedSquare][0].numTokens )
          {

              board[selectedSquare][0].stack = (token *) malloc(sizeof(token));
              board[selectedSquare][0].stack = push(players[j].col, top);
              board[selectedSquare][0].numTokens++;
          }

          if (((numPlayers * i) + j + 1)%NUM_ROWS == 0)
          {
            minNumOfTokens++;
            printf("\t\tminim no. tokens %d\n", minNumOfTokens);
          }
      }
    }

    print_board(board);
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
     return 1;
   }

  void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers){
    int j, choice;
    char direction;

    while (check_win(board, players, numPlayers)) {
      for (size_t i=0; i<numPlayers; i++) {
        srand(time(NULL));    //roll a dice here
        int dice = rand()%5;

        printf("\n\n%s rolled: %d\nAt the end of your turn a token in row %d will be moved\n",
         players[i].name, dice, dice);

         printf("\nDo you wish to move a token? 1 for yes\n");
         scanf("%d", &choice);

         /*
         if (choice == 1) {
          printf("Choose a square with your token in it\n");
          int chooseToken;
          scanf("%d", &chooseToken);

            j=0;
              while (board[chooseToken][j].stack != NULL) {
                j++;    //Loop checks what colum the token to be moved is in
               }

            switch (chooseToken) {
              case(0):   //if top row picked token MUST move down
                board[1][j].stack->col = board[0][j].stack->col;
                break;

              case (5):   //if bottom row picked token MUST move up
                board[5][j].stack->col = board[6][j].stack->col;
                break;

              default:  //else let user pick which direction to move
                printf("What direction to move? (u) or (d)?\n");
                fflush(stdin);
                scanf("%c", &direction);

                if (direction == 'u') {
                  board[chooseToken-1][j].stack->col = board[chooseToken][j].stack->col;
                }
                else if (direction == 'd') {
                  board[chooseToken+1][j].stack->col = board[chooseToken][j].stack->col;
                }
                else {
                  printf("Error, not a valid direction\n");
                }
            }
          }
          */

          j=0;
          while (board[dice][j+1].stack == NULL) {
            j++;    //Loop checks what colum the token to be moved is in
          }
          //Create memory for a token and move one 1 column right
          board[dice][j+1].stack = (token *) malloc(sizeof(token));
          board[dice][j+1].stack = push(board[dice][j].stack->col, top);
          board[dice][j].stack = pop(top);
          printf("\nToken was moved to [%d][%d]", dice, j);
          print_board(board);
      }
     }
   }
