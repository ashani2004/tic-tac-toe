#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tic_tac_toe.h"

int main() {
    int size, mode;
    srand(time(NULL));

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Choose mode:\n");
    printf("1. Two Player (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Player Mode\n");
    printf("Enter choice: ");

    // Input validation for mode
    if (scanf("%d", &mode) != 1 || (mode < 1 || mode > 3)) {
        printf("Invalid mode. Exiting.\n");
        return 1;
    }

    printf("Enter board size (3-10): ");
    // Input validation for size
    if (scanf("%d", &size) != 1 || size < 3 || size > 10) {
        printf("Invalid size. Exiting.\n");
        return 1;
    }

    char **board = initializeBoard(size);
    int moves = 0;
    
    char symbols[3] = {'X', 'O', 'Z'};
    int players = (mode == 3) ? 3 : 2;

    // Clear log file at start
    FILE *file = fopen(LOG_FILE, "w");
    if (!file) {
        printf("Error opening log file.\n");
        freeBoard(board, size); // Clean up
        return 1;
    }
    fclose(file);

    while (1) {
        int currentPlayer = moves % players;
        char symbol = symbols[currentPlayer];

        displayBoard(board, size);
        printf("Player %d (%c)'s turn\n", currentPlayer + 1, symbol);

        if (mode == 2 && currentPlayer == 1) { // Computer is always Player 2 ('O') in mode 2
            computerMove(board, size, symbol);
        } else {
            userMove(board, size, symbol);
        }

        logMove(board, size, currentPlayer + 1, symbol);

        if (checkWin(board, size, symbol)) {
            displayBoard(board, size);
            printf("Player %d (%c) wins!\n", currentPlayer + 1, symbol);
            break;
        }

        if (checkDraw(board, size)) {
            displayBoard(board, size);
            printf("It's a draw!\n");
            break;
        }

        moves++;
    }

    freeBoard(board, size);
    return 0;
}
