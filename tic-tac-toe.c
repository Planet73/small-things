#include <stdio.h>

void printch(int n) {
    if(n == -3) printf("  ");
    else if(n == 0) printf("O ");
    else printf("X ");
}

void show(int m[9]) {
    printch(m[0]); printf("| "); printch(m[1]); printf("| "); printch(m[2]); printf("\n");
    printf("----------\n");
    printch(m[3]); printf("| "); printch(m[4]); printf("| "); printch(m[5]); printf("\n");
    printf("----------\n");
    printch(m[6]); printf("| "); printch(m[7]); printf("| "); printch(m[8]); printf("\n");
}

int max(int m[9], int depth);

int count_empty(int m[9]) {
    int count = 0;
    for(int i = 0; i < 9; ++i) {
        if(m[i] == -3) count++;
    } 
    return count;
}

int xwon(int m[9]) {
    int s1 = m[0] + m[3] + m[6], s2 = m[1] + m[4] + m[7], s3 = m[2] + m[5] + m[8], s4 = m[0] + m[1] + m[2];
    int s5 = m[3] + m[4] + m[5], s6 = m[6] + m[7] + m[8], s7 = m[0] + m[4] + m[8], s8 = m[2] + m[4] + m[6];
    if(s1 == 3 || s2 == 3 || s3 == 3 || s4 == 3 || s5 == 3 || s6 == 3 || s7 == 3 || s8 == 3) return 1;
    else return 0;
}

int owon(int m[9]) {
    int s1 = m[0] + m[3] + m[6], s2 = m[1] + m[4] + m[7], s3 = m[2] + m[5] + m[8], s4 = m[0] + m[1] + m[2];
    int s5 = m[3] + m[4] + m[5], s6 = m[6] + m[7] + m[8], s7 = m[0] + m[4] + m[8], s8 = m[2] + m[4] + m[6];
    if(s1 == 0 || s2 == 0 || s3 == 0 || s4 == 0 || s5 == 0 || s6 == 0 || s7 == 0 || s8 == 0) return 1;
    else return 0;
}

int min(int m[9], int depth) {
    if (xwon(m)) return 1;
    if (owon(m)) return -1;
    if (depth == 0) return 0;

    int best = 2;

    for (int i = 0; i < 9; i++) {
        if (m[i] == -3) {
            m[i] = 0;                // try move
            int val = max(m, depth - 1);
            m[i] = -3;               // undo move
            if (val < best) best = val;
        }
    }
    return best;
}

int max(int m[9], int depth) {
    if (xwon(m)) return 1;
    if (owon(m)) return -1;
    if (depth == 0) return 0;

    int best = -2;

    for (int i = 0; i < 9; i++) {
        if (m[i] == -3) {
            m[i] = 1;                // try move
            int val = min(m, depth - 1);
            m[i] = -3;               // undo move
            if (val > best) best = val;
        }
    }
    return best;
}

int bestMoveX(int m[9]) {
    int bestScore = -2, move = -1;
    
    for(int i = 0; i < 9; ++i) {
        if(m[i] == -3) {
            m[i] = 1;
            int score = min(m, count_empty(m));
            m[i] = -3;

            if(score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int bestMoveO(int m[9]) {
    int bestScore = 2, move = -1;

    for(int i = 0; i < 9; ++i) {
        if(m[i] == -3) {
            m[i] = 0;
            int score = max(m, count_empty(m));
            m[i] = -3;

            if(score < bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int main() {
    // declaring an array and setting all of its values to -3
    int m[9]; for(int i = 0; i < 9; ++i) m[i] = -3;

    // displaying basic instructions
    printf("You will play 'O' and the computer will play 'X'\n");
    
    // asking if user to start or computer to start
    int choice;
    printf("1 if you want to start and 0 if the computer is to start: ");
    scanf("%d", &choice);

    // setting up a bool flag to check if anybody won or the game drew
    int bool = 0;
    
    // if computer starts
    if(!choice) {
        while(count_empty(m) > 0) {
            // making the computer's move
            int comp_move = bestMoveX(m);
            m[comp_move] = 1;

            // showing the user what move the computer made
            printf("The computer made a move on %d\n", comp_move + 1);
            show(m);

            // checking if computer won the game
            if(xwon(m)) {
                printf("COMPUTER WINS!\n");
                bool = 1;
                break;
            }

            // check so there are no loose ends
            if(count_empty(m) == 0) break;

            // making the user's move
            int user_move;
            printf("Make your move: ");
            scanf("%d", &user_move);
            m[user_move - 1] = 0;

            //checking if user won the game
            if(owon(m)) {
                printf("YOU WIN!\n");
                bool = 1;
                break;
            }
        }
    }
    // if user starts 
    else {
        while(count_empty(m) > 0) {
            // making the user's move
            int user_move;
            printf("Make your move: ");
            scanf("%d", &user_move);
            m[user_move - 1] = 0;

            //checking if user won the game
            if(owon(m)) {
                printf("YOU WIN!\n");
                bool = 1;
                break;
            }

            // check so there are no loose ends
            if(count_empty(m) == 0) break;

            // making the computer's move
            int comp_move = bestMoveX(m);
            m[comp_move] = 1;

            // showing the user what move the computer made
            printf("The computer made a move on %d\n", comp_move + 1);
            show(m);

            // checking if computer won the game
            if(xwon(m)) {
                printf("COMPUTER WINS!\n");
                bool = 1;
                break;
            }
        }
    }

    if(!bool) printf("GAME IS A DRAW!\n"); 
    
    return 0;
}

