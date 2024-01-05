#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int NUM_PAWNS = 5;
const int NUM_COLORS = 8;
const int NUM_ATTEMPTS = 10;


enum color_t { RED, GREEN, BLUE, YELLOW, BLACK, WHITE, GRAY, PURPLE };

void generate_hidden_combination(enum color_t hidden_combination[]) {
   
    srand(time(NULL));
    for (int i = 0; i < NUM_PAWNS; ++i) {
        hidden_combination[i] = (enum color_t)(rand() % NUM_COLORS);
    }
}


void read_proposed_combination(enum color_t board[]) {
    printf("Enter your combination (0-7 for colors):\n");
    for (int i = 0; i < NUM_PAWNS; ++i) {
        do {
            printf("Pawn %d: ", i + 1);
            scanf("%d", (int*)&board[i]);
        } while (board[i] < 0 || board[i] >= NUM_COLORS);
    }
}


void evaluate_proposed_combination(enum color_t hidden_combination[],
                                   enum color_t proposed_combination[],
                                   int *num_well_placed_pawns,
                                   int *num_misplaced_pawns) {
    *num_well_placed_pawns = 0;
    *num_misplaced_pawns = 0;

   
    for (int i = 0; i < NUM_PAWNS; ++i) {
        if (proposed_combination[i] == hidden_combination[i]) {
            (*num_well_placed_pawns)++;
        }
    }

   
    for (int i = 0; i < NUM_PAWNS; ++i) {
        for (int j = 0; j < NUM_PAWNS; ++j) {
            if (i != j && proposed_combination[i] == hidden_combination[j]) {
                (*num_misplaced_pawns)++;
                break;
            }
        }
    }
}


void game() {
    enum color_t hidden_combination[NUM_PAWNS];
    enum color_t proposed_combination[NUM_PAWNS];
    int num_well_placed_pawns, num_misplaced_pawns, attempts;

    
    generate_hidden_combination(hidden_combination);

 
    for (attempts = 1; attempts <= NUM_ATTEMPTS; ++attempts) {
        read_proposed_combination(proposed_combination);
        evaluate_proposed_combination(hidden_combination, proposed_combination,
                                      &num_well_placed_pawns, &num_misplaced_pawns);

        printf("Well-placed pawns: %d\n", num_well_placed_pawns);
        printf("Misplaced pawns: %d\n", num_misplaced_pawns);

      
        if (num_well_placed_pawns == NUM_PAWNS) {
            printf("Congratulations! You guessed the combination in %d attempts.\n", attempts);
            break;
        }
    }


    if (attempts > NUM_ATTEMPTS) {
        printf("Sorry, you ran out of attempts. The hidden combination was:");
        for (int i = 0; i < NUM_PAWNS; ++i) {
            printf(" %d", hidden_combination[i]);
        }
        printf("\n");
    }
}


int main() {
    game();

    return 0;
}
