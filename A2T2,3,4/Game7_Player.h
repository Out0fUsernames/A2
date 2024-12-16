#ifndef A2T2_3_4_GAME7_PLAYER_H
#define A2T2_3_4_GAME7_PLAYER_H
#include "BoardGame_Classes.h"

class Game7_Player : public Player<string> {
public:
    Game7_Player(const string& N, const string& s, Board<string>* board): Player<string>(N, s) {
        name = N;
        symbol = s;
        boardPtr = board;
    };

    void getmove(int& x, int& y) override;
};

void Game7_Player::getmove(int &x, int &y) {
    boardPtr->update_board(x, y, "");
    string row = "0", column = "0";
    // Get the value of x (from 1 to 4)
    do {
        cout <<  name << ", enter the row of the cell you want to choose:\n";
        cin >> row;
    } while (row < "1" || row > "4" || row.size() != 1);
    x = stoi(row) - 1;

    // Get the value of y (from 1 to 4)
    do {
        cout << name << ", enter the column of the cell you want to choose:\n";
        cin >> column;
    } while (column < "1" || column > "4" || column.size() != 1);
    y = stoi(column) - 1;
}


class Game7_Random : public RandomPlayer<string> {
public:
    Game7_Random(string s, string n, Board<string> *b) : RandomPlayer<string>(s) {
        dimension = 4;
        name = std::move(n);
        symbol = s;
        srand(static_cast<unsigned int>(time(nullptr)));
        boardPtr = b;
    }

    void getmove(int &x, int &y) override {
        boardPtr->update_board(x, y, symbol + "C");
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, dimension - 1);

        x = dist(gen);
        y = dist(gen);
    }
};


#endif //A2T2_3_4_GAME7_PLAYER_H
