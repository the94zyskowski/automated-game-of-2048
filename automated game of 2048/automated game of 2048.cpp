#include <random>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <conio.h>  // Dla kbhit() i getch()

void initialize_clear_board(int(&array)[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            array[i][j] = 0; //Wype³nij tablicê 0 jako stan pocz¹tkowy.
        }
    }
}

int generate_cell_number() { //wygeneruj numer 2 lub 4
    std::random_device rd; // urz¹dzenie losuj¹ce do zainicjalizowania generatora
    std::mt19937 gen(rd()); // silnik Mersenne Twister
    std::uniform_int_distribution<> distr(0, 1); // rozk³ad jednostajny dla liczb od 0 do 4
    unsigned int coin_flip = distr(gen);
    if (coin_flip == 1) {
        return 4;
    }
    else {
        return 2;
    }

}

int find_any_free_spot(int(&array)[4][4]) {
    int free_spots = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (array[i][j] == 0) {
                free_spots++;
            }
        }
    }
    return free_spots;
}

void win_value_check(int(&array)[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (array[i][j] == 2048) {
                std::cout << "Congratz! Game won!\n"; // GAME WON HERE <----------------------------------------------------
                exit(0);
            }
        }
    }
}

bool pair_check(int tablica[4][4]) {
    // Sprawdzenie w poziomie (w lewo i w prawo)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {  // Sprawdzamy tylko do 3, ¿eby unikn¹æ wyjœcia poza zakres
            if (tablica[i][j] == tablica[i][j + 1]) {
                return true;
            }
        }
    }

    // Sprawdzenie w pionie (góra i dó³)
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {  // Ponownie sprawdzamy do 3, aby unikn¹æ wyjœcia poza zakres
            if (tablica[i][j] == tablica[i + 1][j]) {
                return true;
            }
        }
    }

    return false;  // Jeœli ¿adne warunki nie zosta³y spe³nione, zwracamy false
}

void game_over() {
    std::cout << "Game lost you little bitch!\n"; // GAME OVER HERE <----------------------------------------------------
    exit(0);
}

void fill_random_cell(int(&array)[4][4]) {
    if (find_any_free_spot(array) > 0) {
        std::random_device rd; // urz¹dzenie losuj¹ce do zainicjalizowania generatora
        std::mt19937 gen(rd()); // silnik Mersenne Twister
        std::uniform_int_distribution<> distr(0, 3); // rozk³ad jednostajny dla liczb od 0 do 3
        unsigned int position_x = distr(gen);
        unsigned int position_y = distr(gen);
        while (array[position_y][position_x] != 0) { //Sprawdz czy wygenerowane wspolrzedne kieruja do wypelnionej komorki
            position_x = distr(gen);
            position_y = distr(gen);
        }
        array[position_y][position_x] = generate_cell_number();
    }
    else if (!pair_check(array)){
        game_over();
    }
}

void print_array(int(&array)[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// Funkcja przesuwa elementy wektora i sumuje s¹siaduj¹ce równe wartoœci
std::vector<int> row_sum_left(const std::vector<int>& input_vector) {
    // Tworzymy wektor wyjœciowy o tej samej d³ugoœci co wektor wejœciowy
    // i inicjujemy go zerami
    std::vector<int> not_sorted_output_vector(4, 0);
    std::vector<int> output_vector(4, 0);

    // Zmienna idx bêdzie wskazywaæ, gdzie wstawiamy nastêpn¹ wartoœæ
    // w wektorze wyjœciowym
    int idx = 0;

    // Przechodzimy przez ka¿dy element wektora wejœciowego
    for (int i = 0; i < input_vector.size(); i++) {
        // Sprawdzamy, czy obecny element i nastêpny s¹ takie same
        if (i + 1 < input_vector.size() && input_vector[i] == input_vector[i + 1] ) {
            // Jeœli tak, to sumujemy je i wstawiamy w wektorze wyjœciowym
            not_sorted_output_vector[idx] = input_vector[i] + input_vector[i + 1];
            idx++; // Przesuwamy indeks w wektorze wyjœciowym
            i++; // Przeskakujemy do nastêpnego elementu, poniewa¿ ju¿ go zsumowaliœmy
        }
        else {
            // Jeœli elementy nie s¹ takie same, wstawiamy obecny element
            // do wektora wyjœciowego
            not_sorted_output_vector[idx] = input_vector[i];
            idx++; // Przesuwamy indeks w wektorze wyjœciowym
        }
    }

    idx = 0;
    for (int i = 0; i < not_sorted_output_vector.size(); i++) {
        if (not_sorted_output_vector[i] != 0) {
            output_vector[idx] = not_sorted_output_vector[i];
            idx++;
        }
    }

    // Zwracamy gotowy wektor wyjœciowy
    return output_vector;
}

std::vector<int> row_sum_right(const std::vector<int>& input_vector) {
    std::vector<int> not_sorted_output_vector(4, 0);
    std::vector<int> output_vector(4, 0);

    int idx = 3;

    for (int i = input_vector.size()-1; i >= 0; i--) {
        if (i - 1 >= 0 && input_vector[i] == input_vector[i - 1]) {
            not_sorted_output_vector[idx] = input_vector[i] + input_vector[i - 1];
            idx--;
            i--;
        }
        else {
            not_sorted_output_vector[idx] = input_vector[i];
            idx--;
        }
    }

    idx = 3;
    for (int i = not_sorted_output_vector.size() - 1; i >= 0; i--) {
        if (not_sorted_output_vector[i] != 0) {
            output_vector[idx] = not_sorted_output_vector[i];
            idx--;
        }
    }

    return output_vector;
}

void swipe_horizontal(int(&array)[4][4], char direction) {
    std::vector<int> output_vectors[4];
    for (int i = 0; i < 4; i++) {
        std::vector<int> copied_row(array[i], array[i] + 4);
        if (direction == 'L') {
            output_vectors[i] = row_sum_left(copied_row);
        } else if (direction == 'R') {
            output_vectors[i] = row_sum_right(copied_row);
        }
    }

    // Kopiowanie zawartoœci Ÿród³owej tablicy do docelowej tablicy
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[i][j] = output_vectors[i][j];
        }
    }
}

void swipe_vertical(int(&array)[4][4], char direction) {
    std::vector<int> output_vectors[4];

    for (int column = 0; column < 4; column++) {
        std::vector<int> column_copy;
        for (int i = 0; i < 4; i++) {
            column_copy.push_back(array[i][column]);
        }
        if (direction == 'D') {
            output_vectors[column] = row_sum_right(column_copy);
        }
        else if (direction == 'U') {
            output_vectors[column] = row_sum_left(column_copy);
        }
    }

    // Kopiowanie zawartoœci Ÿród³owej tablicy do docelowej tablicy
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[j][i] = output_vectors[i][j];
        }
    }
}

void swipe_left(int(&array)[4][4]) {
    char direction = 'L';
    swipe_horizontal(array, 'L');
    win_value_check(array);
    fill_random_cell(array);
    std::cout << "\033[H\033[J";
    print_array(array);
}

void swipe_right(int(&array)[4][4]) {
    char direction = 'R';
    swipe_horizontal(array, 'R');
    win_value_check(array);
    fill_random_cell(array);
    std::cout << "\033[H\033[J";
    print_array(array);
}

void swipe_down(int(&array)[4][4]) {
    char direction = 'D';
    swipe_vertical(array, 'D');
    win_value_check(array);
    fill_random_cell(array);
    std::cout << "\033[H\033[J";
    print_array(array);
}

void swipe_up(int(&array)[4][4]) {
    char direction = 'U';
    swipe_vertical(array, 'U');
    win_value_check(array);
    fill_random_cell(array);
    std::cout << "\033[H\033[J";
    print_array(array);
}

int main()
{
    int game_board[4][4];
    initialize_clear_board(game_board);
    for (int i = 0; i < 2; i++) {
        fill_random_cell(game_board);
    }
    print_array(game_board);
    while (true) {
        if (_kbhit()) {  // Jeœli klawisz zosta³ naciœniêty
            char c = _getch();  // Pobierz naciœniêty klawisz
            if (c == 'w') {
                swipe_up(game_board);
            }
            else if (c == 's') {
                swipe_down(game_board);
            }
            else if (c == 'a') {
                swipe_left(game_board);
            }
            else if (c == 'd') {
                swipe_right(game_board);
            }
            else {
                std::cout << "Wrong input! Try: w, s, a or d keys.\n";
            }
        }
    }

}
