#ifndef PYRAMIC_XO_H
#define PYRAMIC_XO_H

#include "BoardGame_Classes.h"
#include <cctype> // for toupper()
#include <iostream>

using namespace std;

// Pyramid Board Class
template <typename T>
class Pyramic_XO_Board : public Board<T> {
public:
    Pyramic_XO_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// Pyramid Player Class
template <typename T>
class Pyramic_XO_Player : public Player<T> {
public:
    Pyramic_XO_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

// Random Player Class
template <typename T>
class Pyramic_XO_Random_Player : public RandomPlayer<T> {
public:
    Pyramic_XO_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

// ----- Implementation -----

// Constructor for Pyramid_XO_Board
template <typename T>
Pyramic_XO_Board<T>::Pyramic_XO_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];

    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            int start = (this->columns - (2 * i + 1)) / 2;
            int end = start + (2 * i + 1);
            if (j >= start && j < end) {
                this->board[i][j] = '.'; // empty cell
            } else {
                this->board[i][j] = '\0'; // unused/invalid positions
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramic_XO_Board<T>::update_board(int x, int y, T mark) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false; // Move out of board bounds
    }

    int start = (this->columns - (2 * x + 1)) / 2;
    int end = start + (2 * x + 1);

    if (y >= start && y < end && this->board[x][y] == '.') {
        this->board[x][y] = toupper(mark); // Place the mark
        this->n_moves++;
        return true;
    }

    return false;
}

template <typename T>
void Pyramic_XO_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        int padding = (this->columns - (2 * i + 1)) / 2;
        cout << string(padding * 2, ' ');

        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] != '\0') {
                cout << (this->board[i][j] == '.' ? '.' : this->board[i][j]) << " ";
            }
        }
        cout << endl;
    }
}

template <typename T>
bool Pyramic_XO_Board<T>::is_win() {
    // Check Columns
    if (this->board[0][2] != '.' && this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]) {
        return true;
    }
    // Check Rows
    for (int i = 0; i < this->rows; i++) {
        int start = (this->columns - (2 * i + 1)) / 2;
        int end = start + (2 * i + 1);
        for (int j = start; j <= end - 3; j++) {
            if (this->board[i][j] != '.' && this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2]) {
                return true;
            }
        }
    }
    // Check Diagonals
    if (this->board[0][2] != '.' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]) {
        return true;
    }
    if (this->board[0][2] != '.' && this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]) {
        return true;
    }

    return false;
}

template <typename T>
bool Pyramic_XO_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramic_XO_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
Pyramic_XO_Player<T>::Pyramic_XO_Player(string name, T symbol)
        : Player<T>(name, symbol)
{
}

template <typename T>
void Pyramic_XO_Player<T>::getmove(int& x, int& y) {
    bool valid = false;
    do {
        cout << "Enter your move (row and column, e.g., 1 3): ";
        cin >> x >> y;

        if (x < 0 || x >= 3 || y < 0 || y >= 5) {
            cout << "Invalid move. Out of range. Try again.\n";
        } else {
            int start = (5 - (2 * x + 1)) / 2;
            int end = start + (2 * x + 1);
            if (y < start || y >= end) {
                cout << "Invalid move. Not within the pyramid structure. Try again.\n";
            } else {
                valid = true;
            }
        }
    } while (!valid);
}

template <typename T>
Pyramic_XO_Random_Player<T>::Pyramic_XO_Random_Player(T symbol)
        : RandomPlayer<T>(symbol)
{
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void Pyramic_XO_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension; // Random number between 0 and 2
    y = rand() % (2 * x + 1); // Ensure the y-coordinate fits pyramid structure
}

#endif // PYRAMIC_XO_H