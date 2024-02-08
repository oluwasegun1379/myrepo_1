#include <stdio.h>

// Function to display the Tic Tac Toe board
void display_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf("---+---+---\n");
    }
}

// Function to check if a player has won
int check_winner(char board[3][3], char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return 1;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;

    return 0;
}

int main() {
    char board[3][3];
    int row, col;
    int moves = 0;
    char player = 'X';

    // Initialize the board with empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    // Game loop
    while (moves < 9) {
        // Display the board
        display_board(board);

        // Get player's move
        printf("Player %c, enter row (1-3) and column (1-3): ", player);
        scanf("%d %d", &row, &col);

        // Check if the move is valid
        if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row - 1][col - 1] = player;
        moves++;

        // Check if the player has won
        if (check_winner(board, player)) {
            display_board(board);
            printf("Player %c wins!\n", player);
            break;
        }

        // Switch to the other player
        player = (player == 'X') ? 'O' : 'X';
    }

    // If no one wins after 9 moves, it's a draw
    if (moves == 9) {
        display_board(board);
        printf("It's a draw!\n");
    }

    return 0;
}

