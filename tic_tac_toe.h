#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define LOG_FILE "tic_tac_toe_log.txt"

// Function Prototypes
char **initializeBoard(int size);
void displayBoard(char **board, int size);
int isValidMove(char **board, int size, int row, int col);
int checkWin(char **board, int size, char symbol);
int checkDraw(char **board, int size);
void freeBoard(char **board, int size);
void logMove(char **board, int size, int player, char symbol);
void userMove(char **board, int size, char symbol);
void computerMove(char **board, int size, char symbol);

#endif
