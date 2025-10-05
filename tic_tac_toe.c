#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tic_tac_toe.h"

char **initializeBoard(int size) {
    char **board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        board[i] = (char *)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
    return board;
}

void displayBoard(char **board, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                printf("---");
                if (k < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int isValidMove(char **board, int size, int row, int col) {
    return (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ');
}

int checkWin(char **board, int size, char symbol) {
    // Check rows and columns
    for (int i = 0; i < size; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) rowWin = 0;
            if (board[j][i] != symbol) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }

    // Check diagonals
    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != symbol) diag1 = 0;
        if (board[i][size - i - 1] != symbol) diag2 = 0;
    }
    return (diag1 || diag2);
}

int checkDraw(char **board, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ')
                return 0; // Found an empty spot, not a draw
    return 1; // Board is full
}

void freeBoard(char **board, int size) {
    for (int i = 0; i < size; i++) free(board[i]);
    free(board);
}

void logMove(char **board, int size, int player, char symbol) {
    FILE *file = fopen(LOG_FILE, "a");
    if (!file) return;

    fprintf(file, "Player %d (%c) made a move\n", player, symbol);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(file, " %c ", board[i][j]);
            if (j < size - 1) fprintf(file, "|");
        }
        fprintf(file, "\n");
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                fprintf(file, "---");
                if (k < size - 1) fprintf(file, "+");
            }
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n");
    fclose(file);
}

void userMove(char **board, int size, char symbol) {
    int row, col;
    while (1) {
        printf("Enter row and column (0-%d): ", size - 1);
        if (scanf("%d %d", &row, &col) != 2) {
            // Error fix: Clear input buffer on non-integer input
            printf("Invalid input. Please enter two numbers.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        if (isValidMove(board, size, row, col)) {
            board[row][col] = symbol;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

void computerMove(char **board, int size, char symbol) {
    int row, col;
    do {
        row = rand() % size;
        col = rand() % size;
    } while (!isValidMove(board, size, row, col));
    board[row][col] = symbol;
    printf("Computer placed at (%d, %d)\n", row, col);
}
