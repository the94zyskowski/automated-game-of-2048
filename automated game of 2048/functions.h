#include <vector>

void initialize_clear_board(int(&array)[4][4]);

int generate_cell_number();

int find_any_free_spot(int(&array)[4][4]);

void win_value_check(int(&array)[4][4]);

bool pair_check(int tablica[4][4]);

void game_over();

void fill_random_cell(int(&array)[4][4]);

void print_array(int(&array)[4][4]);

std::vector<int> row_sum_left(const std::vector<int>& input_vector, int& score);

std::vector<int> row_sum_right(const std::vector<int>& input_vector, int& score);

void swipe_horizontal(int(&array)[4][4], char direction, int& score);

void swipe_vertical(int(&array)[4][4], char direction, int& score);

void swipe_left(int(&array)[4][4], int& score);

void swipe_right(int(&array)[4][4], int& score);

void swipe_down(int(&array)[4][4], int& score);

void swipe_up(int(&array)[4][4], int& score);
#pragma once
