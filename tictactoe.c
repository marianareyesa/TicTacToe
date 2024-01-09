#include <stdio.h>

char game_grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
};

// Function to save the current game state to a file
void saveGameState() {
    FILE *fp;
    fp = fopen("game_state.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(fp, "%c", game_grid[i][j]);
            if (j < 2) {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Game state saved successfully.\n");
}

void loadGameState() {
    FILE *fp;
    fp = fopen("game_state.txt", "r");
    if (fp == NULL) {
        printf("No saved game state found.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fscanf(fp, " %c", &game_grid[i][j]);
            fseek(fp, 1, SEEK_CUR);  // Move the file pointer to skip the space character
        }
    }

    fclose(fp);
    printf("Game state loaded successfully.\n");
}

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

void play() {
    //Defining the players
    char player_x = 'x';
    char player_o = 'o';
    int turns = 2;
    int choice;

    char currentPlayer = 'x';

    //Making moves until one of them wins, or it is a draw
    while(checkWin(game_grid, player_x) == 0 && checkWin(game_grid, player_o) == 0 && isDraw(game_grid) == 0){
        if(turns % 2 == 0){ // x plays
            printf("%s", "Where do you want to play your x (1-9)?\n");
            printf("%s", "1. Top left \n2. Top middle \n3. Top right \n4. Middle left \n5. Middle \n6. Middle right\n7. Bottom left \n8. Bottom middle \n9. Bottom rigth\n");
            scanf("%d", &choice);
            //Check if it is a valid move
            if(isValidMove(game_grid, choice) == 1){
                int row = (choice - 1) / 3;
                int column = (choice - 1) % 3;
                game_grid[row][column] = player_x;
                turns++;
            } else{
                printf("%s", "Invalid move, try again!\n");
            }
        } else { //o plays
            printf("%s", "Where do you want to play your o (1-9)?\n");
            printf("%s", "1. Top left \n2. Top middle \n3. Top right \n4. Middle left \n5. Middle \n6. Middle right\n7. Bottom left \n8. Bottom middle \n9. Bottom rigth\n");
            scanf("%d", &choice);
            //Check if it is a valid move
            if(isValidMove(game_grid, choice) == 1){
                int row = (choice - 1) / 3;
                int column = (choice - 1) % 3;
                game_grid[row][column] = player_o;
                turns++;
            } else{
                printf("%s", "Invalid move, try again!\n");
            }
        }
        displayGrid(game_grid);

        // Save the game state after each move if the game is not won
        if (checkWin(game_grid, player_x) == 0 && checkWin(game_grid, player_o) == 0 && isDraw(game_grid) == 0) {
            saveGameState();
        }
    }

    // Determine the winner or if it's a draw
    if (checkWin(game_grid, player_x)) {
        printf("Player X wins!\n");
    } else if (checkWin(game_grid, player_o)) {
        printf("Player O wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    displayGrid(game_grid);
}

int main(void){
    int choice;
    printf("Do you want to reload a previous game? (1 for yes)\n");
    scanf("%d", &choice);

    if (choice == 1) {
        loadGameState();
        displayGrid(game_grid);
    }

    play();

    return 0;
}