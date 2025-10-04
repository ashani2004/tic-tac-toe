#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

char board[SIZE][SIZE];
FILE *logFile;

void initializeBoard();
void printBoard();
int checkWinner();
int isFull();
void userMove();
void computerMove();
void logMove(char player, int row, int col);

int main() {
    int winner = 0;
    int row, col;
    srand(time(0));

    logFile = fopen("game_log.txt", "w");
    if (logFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    initializeBoard();
    printf("Welcome to Tic Tac Toe (User vs Computer)\n");

    while (1) {
        printBoard();
        userMove();
        if ((winner = checkWinner()) != 0 || isFull()) break;

        computerMove();
        if ((winner = checkWinner()) != 0 || isFull()) break;
    }

    printBoard();
    if (winner == 1)
        printf("You win!\n");
    else if (winner == 2)
        printf("Computer wins!\n");
    else
        printf("It's a draw!\n");

    fclose(logFile);
    return 0;
}

void initializeBoard() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1)
            printf("---+---+---\n");
    }
    printf("\n");
}

int checkWinner() {
    
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return (board[i][0] == 'X') ? 1 : 2;

        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return (board[0][i] == 'X') ? 1 : 2;
    }

    if (board[0][0] != ' ' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return (board[0][0] == 'X') ? 1 : 2;

    if (board[0][2] != ' ' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return (board[0][2] == 'X') ? 1 : 2;

    return 0;
}

int isFull() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void userMove() {
    int row, col;
    while (1) {
        printf("Enter your move (row and column: 1-3 1-3): ");
        scanf("%d %d", &row, &col);
        row--; col--;

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
            board[row][col] = 'X';
            logMove('X', row, col);
            break;
        } else {
            printf("Invalid move, try again.\n");
        }
    }
}

void computerMove() {
    int row, col;
    printf("Computer's turn...\n");
    while (1) {
        row = rand() % SIZE;
        col = rand() % SIZE;
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            logMove('O', row, col);
            break;
        }
    }
}

void logMove(char player, int row, int col) {
    fprintf(logFile, "Player %c -> Row: %d, Col: %d\n", player, row + 1, col + 1);
}
