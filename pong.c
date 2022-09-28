// Copyright 2022 Shinoxy at School 21

#include <stdio.h>
#include <stdlib.h>
void renderMap(int racket_1, int racket_2,
               int score_1, int score_2,
               int ball_x, int ball_y);
void MoveBall();
void respawn(int* ball_x, int* ball_y,
             int* racket_1_y, int* racket_2_y,
             int* score_1, int* score_2);

int main() {
    int racket_1 = 12, racket_2 = 12;
    int score_1 = 0, score_2 = 0;
    int ball_y = 13, ball_x = 40;
    int vector_x = 1, vector_y = -1;
    renderMap(racket_1, racket_2, score_1, score_2, ball_x, ball_y);
    printf("\nPLAYER 1: press A-Z for action.\n");
    printf("PLAYER 2: press K-M for action.\n");
    printf("Press Q to quit.\n\n");
    while (score_1 <= 21 || score_2 <= 21) {
        char action = ' ';
            if (action == 'a' || action == 'A') {
                if (racket_1 <= 2)
                    printf(" ");
                else
                    racket_1--;
            }
            if (action == 'z' || action == 'Z') {
                if (racket_1 >=22)
                    printf(" ");
                else
                    racket_1++;
            }
            if (action == 'k' || action == 'K') {
                if (racket_2 <= 2)
                    printf(" ");
                else
                    racket_2--;
            }
            if (action == 'm' || action == 'M') {
                if (racket_2 >=22)
                    printf(" ");
                else
                    racket_2++;
            }
            if (action == 'q' || action == 'Q') {  // Press to quit the game
                printf("\nSee you later!");
                return 0;
            }
            MoveBall(&ball_x, &ball_y,
                     &vector_x, &vector_y,
                     &racket_1, &racket_2,
                     &score_1, &score_2);
            renderMap(racket_1, racket_2, score_1, score_2, ball_x, ball_y);
            if (score_1 == 21) {
                printf("PLAYER 1 WIN!\nSCORE:%d:%d\n", score_1, score_2);
                break;
            }
            if (score_2 == 21) {
                printf("PLAYER 2 WIN!\nSCORE:%d:%d\n", score_1, score_2);
                break;
            }
    }
    return 0;
}
void renderMap(int racket_1, int racket_2,
               int score_1, int score_2,
               int ball_x, int ball_y) {
    printf("\e[1;1H\e[2J");
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++) {
            if (y == 25) {
                printf("#");
            } else if (y == 1) {
                if (x == 38)
                    printf("\e[1(;32)m%02d|%02d\e[0(;0)m", score_1, score_2);
                if (x <= 80 && x >= 76)
                    printf(" ");
                else
                    printf("#");
            } else {
                    if (x == 1 || x == 80) {
                        printf("#");
                    } else {
                        if (y == ball_y && x == ball_x) {
                            printf("o");
                            continue;
                        }
                        if (x == 40)
                            printf("|");
                        else if ((x == 5 && y == racket_1) ||
                                 (x == 5 && y == racket_1 + 1) ||
                                 (x == 5 && y == racket_1 + 2))
                            printf("|");
                        else if ((x == 76 && y == racket_2) ||
                                 (x == 76 && y == racket_2 + 1) ||
                                 (x == 76 && y == racket_2 + 2))
                            printf("|");
                        else
                            printf(" ");
                    }
            }
        }
        printf("\n");
    }
}

void MoveBall(int* ball_x, int* ball_y,
              int* vector_x, int* vector_y,
              int* racket_1, int* racket_2,
              int* score_1, int* score_2) {
    if (*ball_y == 2 || *ball_y == 24)
        *vector_y *= -1;
    if (*ball_x == 6 &&
        (*ball_y == *racket_1 + 1 ||
         *ball_y == *racket_1 + 2 ||
         *ball_y == *racket_1))
        *vector_x *= -1;
    if (*ball_x == 75 &&
        (*ball_y == *racket_2 + 1 ||
         *ball_y == *racket_2 + 2 ||
         *ball_y == *racket_2))
        *vector_x *= -1;
    *ball_y += *vector_y;
    *ball_x += *vector_x;
    if (*ball_x < 6 &&
        (*ball_y != *racket_1 ||
         *ball_y != *racket_1 + 1 ||
         *ball_y != *racket_1 + 2)) {
        *score_2 += 1;
        *ball_y = 13, *ball_x = 40;
    }
    if (*ball_x > 75 &&
        (*ball_y != *racket_2 ||
         *ball_y != *racket_2 + 1 ||
         *ball_y != *racket_2 + 2)) {
        *score_1 += 1;
        *ball_y = 13, *ball_x = 40;
    }
}
