#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void printBoard();
int checkWin();
int getComputerMove();
int minimax(char board[], int depth, int isMaximizingPlayer);
int alphabeta(char board[], int depth, int alpha, int beta, int isMaximizingPlayer);

char board[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void main() {
    int player = 1, input, status = -1;
    printBoard();

    while (status == -1) {
        player = (player % 2 == 0) ? 2 : 1;
        char mark = (player == 1) ? 'X' : 'O';

        if (player == 1) {
            printf("Please enter a number for your move: ");
            scanf("%d", &input);
            if (input < 1 || input > 9) {
                printf("Invalid input\n");
                continue;
            }
        } else {
            input = getComputerMove();
	    printf("Computer's move: %d\n", input);
	    getch();
        }

        if (board[input] == 'X' || board[input] == 'O') {
            printf("That spot is already taken, please try again.\n");
            continue;
        }

        board[input] = mark;
        printBoard();

        int result = checkWin();

        if (result == 1) {
            printf("Player %d is the Winner", player);
            getch();
            return;
        } else if (result == 0) {
            printf("It's a draw!");
            getch();
            return;
        }

        player++;
    }
}

int getComputerMove() {
    int bestScore = -1000;
    int bestMove = -1;

    for (int i = 1; i <= 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            board[i] = 'O';
            int score = alphabeta(board, 0, -1000, 1000, 0);
            board[i] = (char)('0' + i);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

int alphabeta(char board[], int depth, int alpha, int beta, int isMaximizingPlayer) {
    int result = checkWin();
    if (result != -1) {
        if (result == 0) return 0;
        else if (result == 1) return isMaximizingPlayer ? -1 : 1;
    }

    if (isMaximizingPlayer) {
        int bestScore = -1000;
        for (int i = 1; i <= 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                board[i] = 'O';
                int score = alphabeta(board, depth + 1, alpha, beta, 0);
                board[i] = (char)('0' + i);
                bestScore = (score > bestScore) ? score : bestScore;
                alpha = (alpha > bestScore) ? alpha : bestScore;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 1; i <= 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                board[i] = 'X';
                int score = alphabeta(board, depth + 1, alpha, beta, 1);
                board[i] = (char)('0' + i);
                bestScore = (score < bestScore) ? score : bestScore;
                beta = (beta < bestScore) ? beta : bestScore;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
}void printBoard(){
    system("cls");
    printf("\n\n");
    printf("=== TIC TAC TOE ===\n\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",board[1],board[2],board[3]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",board[4],board[5],board[6]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",board[7],board[8],board[9]);
    printf("     |     |     \n");
    printf("\n\n");
}


int checkWin(){

    if(board[1]==board[2] && board[2]==board[3]){
	return 1;
    }
    if(board[1]==board[4] && board[4]==board[7]){
	return 1;
    }
    if(board[7]==board[8] && board[8]==board[9]){
	return 1;
    }
    if(board[3]==board[6] && board[6]==board[9]){
	return 1;
    }
    if(board[1]==board[5] && board[5]==board[9]){
	return 1;
    }
    if(board[3]==board[5] && board[5]==board[7]){
	return 1;
    }
    if(board[2]==board[5] && board[5]==board[8]){
	return 1;
    }
    if(board[4]==board[5] && board[5]==board[6]){
	return 1;
    }

    int count=0;
    for (int i = 1; i <=9; i++)
    {
	if(board[i]=='X' || board[i]=='O'){
	    count++;
	}
    }

    if(count==9){
	return 0;
    }
    return -1;
}
