#include <stdio.h>
#include <stdlib.h>

char** initializeBoard(int n);
void displayBoard(char** board, int n);
int acceptInput(int* row, int* col, int n);
int validateMove(char** board, int row, int col, int n);
int checkWin(char** board, int n, char player);
int checkDraw(char** board, int n);
void logBoard(FILE* logFile, char** board, int n);

int main() {
    int n;
    printf("Enter board size (3 to 10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Invalid size. Please choose between 3 and 10.\n");
        return 1;
    }

    char** board = initializeBoard(n);

    FILE* logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        printf("Error opening log file!\n");
        return 1;
    }

    int row, col, moves = 0;
    char currentPlayer = 'X';

    while (1) {
        displayBoard(board, n);
        printf("Player %c, enter your move (row col): ", currentPlayer);

        if (!acceptInput(&row, &col, n)) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (!validateMove(board, row, col, n)) {
            printf("Invalid move! Cell already taken or out of range.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        moves++;

      
        logBoard(logFile, board, n);

        if (checkWin(board, n, currentPlayer)) {
            displayBoard(board, n);
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (checkDraw(board, n)) {
            displayBoard(board, n);
            printf("It's a draw!\n");
            break;
        }

       
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
    fclose(logFile);

    return 0;
}

char** initializeBoard(int n) {
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
    return board;
}

void displayBoard(char** board, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                printf("---");
                if (j < n - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int acceptInput(int* row, int* col, int n) {
    if (scanf("%d %d", row, col) != 2) {
        while (getchar() != '\n'); 
        return 0;
    }
    return 1;
}

int validateMove(char** board, int row, int col, int n) {
    if (row < 0 || row >= n || col < 0 || col >= n) return 0;
    if (board[row][col] != ' ') return 0;
    return 1;
}

int checkWin(char** board, int n, char player) {
    int i, j;

   
    for (i = 0; i < n; i++) {
        int win = 1;
        for (j = 0; j < n; j++) {
            if (board[i][j] != player) { win = 0; break; }
        }
        if (win) return 1;
    }

    for (j = 0; j < n; j++) {
        int win = 1;
        for (i = 0; i < n; i++) {
            if (board[i][j] != player) { win = 0; break; }
        }
        if (win) return 1;
    }

    int win = 1;
    for (i = 0; i < n; i++) {
        if (board[i][i] != player) { win = 0; break; }
    }
    if (win) return 1;

    win = 1;
    for (i = 0; i < n; i++) {
        if (board[i][n - i - 1] != player) { win = 0; break; }
    }
    if (win) return 1;

    return 0;
}


int checkDraw(char** board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}


void logBoard(FILE* logFile, char** board, int n) {
    fprintf(logFile, "\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(logFile, " %c ", board[i][j]);
            if (j < n - 1) fprintf(logFile, "|");
        }
        fprintf(logFile, "\n");
        if (i < n - 1) {
            for (int j = 0; j < n; j++) {
                fprintf(logFile, "---");
                if (j < n - 1) fprintf(logFile, "+");
            }
            fprintf(logFile, "\n");
        }
    }
    fprintf(logFile, "\n");
}
