#include <stdio.h>
#include <CUnit/Basic.h>

//Display grid in current state
void displayGrid(char game_grid[3][3]){
    //Do a for loop to iterate through the matrix
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%c", game_grid[i][j]);
            if (j < 2) {
                printf(" | "); // Add vertical line
            }
        }
        printf("%s", "\n");
        if (i < 2) {
            printf("---------\n"); // Add horizontal lines
        }
    }
    printf("%s", "\n");
}

//Checking if a player wins the game
int checkWin(char game_grid[3][3], char player){
    //8 possible ways of winning
    for (int i = 0; i < 3; i++) {
        if (game_grid[i][0] == player && game_grid[i][1] == player && game_grid[i][2] == player) {
            return 1; // Row win
        }
        if (game_grid[0][i] == player && game_grid[1][i] == player && game_grid[2][i] == player) {
            return 1; // Column win
        }
    }
    if (game_grid[0][0] == player && game_grid[1][1] == player && game_grid[2][2] == player) {
        return 1; // Diagonal win (top-left to bottom-right)
    }
    if (game_grid[0][2] == player && game_grid[1][1] == player && game_grid[2][0] == player) {
        return 1; // Diagonal win (top-right to bottom-left)
    }
    return 0; // No win
}

//Check if inputs provided by the user are valid
int isValidMove(char game_grid[3][3], int choice){
    int row = (choice - 1) / 3;
    int column = (choice - 1) % 3;
    if (choice >= 1 && choice <= 9 && game_grid[row][column] == ' ') {
        return 1; // Valid move
    } else {
        return 0; // Invalid move
    }
}

//Check if the game is a draw
int isDraw(char game_grid[3][3]){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game_grid[i][j] == ' ') {
                return 0; // Game is not a draw
            }
        }
    }
    return 1; // Game is a draw
}

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_isValidMove(void) {
  char game_grid[3][3] = {
        {' ', ' ', ' '},
       {' ', ' ', ' '},
         {' ', ' ', ' '}
  };

  CU_ASSERT(isValidMove(game_grid, 5) == 1); // Valid move
  CU_ASSERT(isValidMove(game_grid, 10) == 0); // Invalid move
}

void test_checkWin(void) {
    char game_grid[3][3] = {
            {'x', 'o', 'x'},
            {' ', 'x', 'o'},
            {'o', ' ', 'x'}
    };

    CU_ASSERT(checkWin(game_grid, 'x') == 1); // X wins
    CU_ASSERT(checkWin(game_grid, 'o') == 0); // O doesn't win
    // Add more test cases as needed
}

void test_isDraw(void) {
    char game_grid[3][3] = {
            {'x', 'o', 'x'},
            {'x', 'x', 'o'},
            {'o', 'x', 'o'}
    };

    CU_ASSERT(isDraw(game_grid) == 1); // draw
    // Add more test cases as needed
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("TicTacToe_Test_Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    //(NULL == CU_add_test(pSuite, "test of isValidMove", test_isValidMove)) ||
    if ((NULL == CU_add_test(pSuite, "test of isValidMove", test_isValidMove)) ||
    (NULL == CU_add_test(pSuite, "test of checkWin", test_checkWin)) ||
    (NULL == CU_add_test(pSuite, "test of isDraw", test_isDraw))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}