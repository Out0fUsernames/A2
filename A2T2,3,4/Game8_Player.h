#ifndef A2T2_3_4_GAME8_PLAYER_H
#define A2T2_3_4_GAME8_PLAYER_H
#include <utility>

#include "BoardGame_Classes.h"

class Game8_Player : public Player<string> {
public:
    Game8_Player(const string& N, const string& s): Player<string>(N, s) {
        name = N;
        symbol = s;
    };

    void getmove(int &x, int &y) override;
};

void Game8_Player::getmove(int &x, int &y) {
    string row = "0", column = "0";
    // Get the value of x (from 1 to 9)
    do {
        cout <<  name << ", enter the row of the cell you want to choose:\n";
        cin >> row;
    } while (row < "1" || row > "9" || row.size() != 1);
    x = stoi(row) - 1;

    // Get the value of y (from 1 to 9)
    do {
        cout << name << ", enter the column of the cell you want to choose:\n";
        cin >> column;
    } while (column < "1" || column > "9" || column.size() != 1);
    y = stoi(column) - 1;
}


class Game8_Random : public RandomPlayer<string> {
public:
    Game8_Random(const string& s, string n) : RandomPlayer<string>(s) {
        dimension = 9;
        name = std::move(n);
        symbol = s;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int &x, int &y) override {
        x = rand() % dimension;  // Random number between 0 and 2
        y = rand() % dimension;
    }
};


#endif //A2T2_3_4_GAME8_PLAYER_H
