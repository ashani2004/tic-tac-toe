#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **board;
int N;
FILE *logFile;
char players[3] = {'X', 'O', 'Z'};

void initBoard();
void printBoard();
int checkWinner();
int isFull();
void userMove(char symbol);
void computerMove(char symbol);
void logMove(char player, int row, int col);

int main() {
    int winner = 0, turn = 0;
    srand(time(0));

    printf("Enter board size (3 - 10): ");
    scanf("%d", &N);
    if (N < 3 || N > 10) {
        printf("Invalid size!\n");
        return 1;
    }

    board = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++)
        board[i] = (char *)malloc(N * sizeof(char));

    logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        printf("Error opening file.\n");
        return 1;
    }

    initBoard();
    printf("=== Multi-Player Tic Tac Toe ===\n");
    printf("Players: X (User), O (Computer1), Z (Computer2)\n");

    while (1) {
        printBoard();
        char current = players[turn];
        printf("Turn: Player %c\n", current);

        if (current == 'X') userMove(current);
        else computerMove(current);

        if ((winner = checkWinner()) != 0 || isFull()) break;
        turn = (turn + 1) % 3; 
    }

    printBoard();
    if (winner == 1) printf("Player X wins!\n");
    else if (winner == 2) printf("Player O wins!\n");
    else if (winner == 3) printf("Player Z wins!\n");
    else printf("It's a draw!\n");

    fclose(logFile);
    for (int i = 0; i < N; i++) free(board[i]);
    free(board);
    return 0;
}

void initBoard() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        printf("\n");
        if (i < N - 1) {
            for (int k = 0; k < N; k++) printf("---");
            printf("\n");
        }
    }
    printf("\n");
}

void userMove(char symbol) {
    int r, c;
    while (1) {
        printf("Enter row and column (1-%d): ", N);
        scanf("%d %d", &r, &c);
        r--; c--;
        if (r >= 0 && r < N && c >= 0 && c < N && board[r][c] == ' ') {
            board[r][c] = symbol;
            logMove(symbol, r, c);
            break;
        } else printf("Invalid move!\n");
    }
}

void computerMove(char symbol) {
    int r, c;
    printf("Computer (%c) playing...\n", symbol);
    while (1) {
        r = rand() % N;
        c = rand() % N;
        if (board[r][c] == ' ') {
            board[r][c] = symbol;
            logMove(symbol, r, c);
            break;
        }
    }
}

int checkWinner() {
    for (int i = 0; i < N; i++) {
        int rowSame = 1, colSame = 1;
        for (int j = 1; j < N; j++) {
            if (board[i][j] != board[i][0] || board[i][0] == ' ') rowSame = 0;
            if (board[j][i] != board[0][i] || board[0][i] == ' ') colSame = 0;
        }
        if (rowSame)
            return (board[i][0] == 'X') ? 1 : (board[i][0] == 'O' ? 2 : 3);
        if (colSame)
            return (board[0][i] == 'X') ? 1 : (board[0][i] == 'O' ? 2 : 3);
    }

    int d1 = 1, d2 = 1;
    for (int i = 1; i < N; i++) {
        if (board[i][i] != board[0][0] || board[0][0] == ' ') d1 = 0;
        if (board[i][N - i - 1] != board[0][N - 1] || board[0][N - 1] == ' ') d2 = 0;
    }
    if (d1)
        return (board[0][0] == 'X') ? 1 : (board[0][0] == 'O' ? 2 : 3);
    if (d2)
        return (board[0][N - 1] == 'X') ? 1 : (board[0][N - 1] == 'O' ? 2 : 3);

    return 0;
}

int isFull() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

void logMove(char player, int row, int col) {
    fprintf(logFile, "Player %c -> Row: %d, Col: %d\n", player, row + 1, col + 1);
}
