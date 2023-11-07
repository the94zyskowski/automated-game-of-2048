#include <iostream>
#include <vector>
#include <conio.h>  // Dla kbhit() i getch()
#include "functions.h"

int main()
{
    int game_board[4][4];
    int score = 0;
    initialize_clear_board(game_board);
    for (int i = 0; i < 2; i++) {
        fill_random_cell(game_board);
    }
    print_array(game_board);
    std::cout << "Score: " << score << "\n";
    while (true) {
        if (_kbhit()) {  // Jeœli klawisz zosta³ naciœniêty
            char c = _getch();  // Pobierz naciœniêty klawisz
            if (c == 'w') {
                swipe_up(game_board, score);
            }
            else if (c == 's') {
                swipe_down(game_board, score);
            }
            else if (c == 'a') {
                swipe_left(game_board, score);
            }
            else if (c == 'd') {
                swipe_right(game_board, score);
            }
            else {
                std::cout << "Wrong input! Try: w, s, a or d keys.\n";
            }
        }
    }

}
