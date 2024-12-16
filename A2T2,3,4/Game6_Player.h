#ifndef A2T2_3_4_GAME6_PLAYER_H
#define A2T2_3_4_GAME6_PLAYER_H
#include <utility>

#include "BoardGame_Classes.h"

class Game6_Player : public Player<string> {
    string real_name;
public:
    // Constructor
    Game6_Player(string r_name, const string& s, string N) : Player(std::move(N), s) {
        real_name = std::move(r_name);
        symbol = s;
    }

    // Class method
        void getmove(int &x, int &y) override;
};

void Game6_Player::getmove(int &x, int &y) {
    string row = "0", column = "0";
    // Get the value of x ( from 1 to 3)
    do {
        cout <<  real_name << ", enter the row of the cell you want to choose:\n";
        cin >> row;
    } while (row < "1" || row > "3" || row.size() != 1);
    x = stoi(row) - 1;

    // Get the value of y ( from 1 to 3)
    do {
        cout << real_name << ", enter the column of the cell you want to choose:\n";
        cin >> column;
    } while (column < "1" || column > "3" || column.size() != 1);
    y = stoi(column) - 1;
}


class Game6_Random : public RandomPlayer<string> {
public:
    Game6_Random(string s, string n) : RandomPlayer<string>(s) {
        dimension = 3;
        name = n;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int &x, int &y) override {
        x = rand() % dimension;
        y = rand() % dimension;
    }
};
#endif //A2T2_3_4_GAME6_PLAYER_H
