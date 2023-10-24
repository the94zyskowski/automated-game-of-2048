#include <random>
#include <iostream>
#include <vector>

void initialize_clear_board(int(&array)[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            array[i][j] = -1; //Wype�nij tablic� -1 jako stan pocz�tkowy.
        }
    }
}

int generate_cell_number() { //wygeneruj numer 2 lub 4
    std::random_device rd; // urz�dzenie losuj�ce do zainicjalizowania generatora
    std::mt19937 gen(rd()); // silnik Mersenne Twister
    std::uniform_int_distribution<> distr(0, 1); // rozk�ad jednostajny dla liczb od 0 do 4
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
            if (array[i][j] == -1) {
                free_spots++;
            }
        }
    }
    return free_spots;
}

void fill_random_cell(int(&array)[4][4]) {
    if (find_any_free_spot(array) > 0) {
        std::random_device rd; // urz�dzenie losuj�ce do zainicjalizowania generatora
        std::mt19937 gen(rd()); // silnik Mersenne Twister
        std::uniform_int_distribution<> distr(0, 3); // rozk�ad jednostajny dla liczb od 0 do 3
        unsigned int position_x = distr(gen);
        unsigned int position_y = distr(gen);
        while (array[position_y][position_x] != -1) { //Sprawdz czy wygenerowane wspolrzedne kieruja do wypelnionej komorki
            position_x = distr(gen);
            position_y = distr(gen);
        }
        array[position_y][position_x] = generate_cell_number();
    }
    else {
        std::cout << "Game lost you little bitch!\n"; // GAME OVER HERE <----------------------------------------------------
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

// Funkcja przesuwa elementy wektora i sumuje s�siaduj�ce r�wne warto�ci
std::vector<int> row_sum_left(const std::vector<int>& input_vector) {
    // Tworzymy wektor wyj�ciowy o tej samej d�ugo�ci co wektor wej�ciowy
    // i inicjujemy go zerami
    std::vector<int> not_sorted_output_vector(4, 0);
    std::vector<int> output_vector(4, 0);

    // Zmienna idx b�dzie wskazywa�, gdzie wstawiamy nast�pn� warto��
    // w wektorze wyj�ciowym
    int idx = 0;

    // Przechodzimy przez ka�dy element wektora wej�ciowego
    for (int i = 0; i < input_vector.size(); i++) {
        // Sprawdzamy, czy obecny element i nast�pny s� takie same
        if (i + 1 < input_vector.size() && input_vector[i] == input_vector[i + 1] ) {
            // Je�li tak, to sumujemy je i wstawiamy w wektorze wyj�ciowym
            not_sorted_output_vector[idx] = input_vector[i] + input_vector[i + 1];
            idx++; // Przesuwamy indeks w wektorze wyj�ciowym
            i++; // Przeskakujemy do nast�pnego elementu, poniewa� ju� go zsumowali�my
        }
        else {
            // Je�li elementy nie s� takie same, wstawiamy obecny element
            // do wektora wyj�ciowego
            not_sorted_output_vector[idx] = input_vector[i];
            idx++; // Przesuwamy indeks w wektorze wyj�ciowym
        }
    }

    idx = 0;
    for (int i = 0; i < not_sorted_output_vector.size(); i++) {
        if (not_sorted_output_vector[i] != 0) {
            output_vector[idx] = not_sorted_output_vector[i];
            idx++;
        }
    }

    // Zwracamy gotowy wektor wyj�ciowy
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

void swipe(int(&array)[4][4], char direction) {
    std::vector<int> output_vectors[4];
    for (int i = 0; i < 4; i++) {
        std::vector<int> copied_row(array[i], array[i] + 4);
        if (direction == 'L') {
            output_vectors[i] = row_sum_left(copied_row);
        } else if (direction == 'R') {
            output_vectors[i] = row_sum_right(copied_row);
        }
    }

    // Kopiowanie zawarto�ci �r�d�owej tablicy do docelowej tablicy
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            array[i][j] = output_vectors[i][j];
        }
    }
}

void swipe_left(int(&array)[4][4]) {
    char direction = 'L';
    swipe(array, 'L');
}

void swipe_right(int(&array)[4][4]) {
    char direction = 'R';
    swipe(array, 'R');
}

int main()
{
    int game_board[4][4];
    initialize_clear_board(game_board);
    for (int i = 0; i < 16; i++) {
        fill_random_cell(game_board);
    }
    std::cout << "Generated array:\n";
    print_array(game_board);
    std::cout << "\n";

    std::cout << "Array after one 'swipe right':\n";
    swipe_right(game_board);
    print_array(game_board);
    std::cout << "\n";

    std::cout << "Array after one 'swipe left':\n";
    swipe_left(game_board);
    print_array(game_board);
    std::cout << "\n";

    std::cout << "Array after one 'swipe right':\n";
    swipe_right(game_board);
    print_array(game_board);
    std::cout << "\n";

    std::cout << "Array after one 'swipe left':\n";
    swipe_left(game_board);
    print_array(game_board);
    std::cout << "\n";

}
