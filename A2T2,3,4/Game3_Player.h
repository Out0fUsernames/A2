#ifndef A2T2_3_4_GAME3_PLAYER_H
#define A2T2_3_4_GAME3_PLAYER_H
#include "BoardGame_Classes.h"

class Game3_Player : public Player<string>{
    static int* n_moves;
public:
    Game3_Player(const string& N, const string& s): Player<string>(N, s) {
        name = N;
        symbol = s;
    };
    ~Game3_Player();
    void getmove(int &x, int &y) override;
    static void set_moves(int& moves);
};

int* Game3_Player::n_moves = nullptr;

Game3_Player::~Game3_Player() {
    n_moves = nullptr;
    delete n_moves;
}

void Game3_Player::getmove(int &x, int &y) {
    if (*n_moves != 24){
        string row = "0", column = "0";
        // Get the value of x ( from 1 to 5)
        do {
            cout << "Player " << name << ", enter the row of the cell you want to choose:\n";
            cin >> row;
        } while (row < "1" || row > "5" || row.size() != 1);
        x = stoi(row) - 1;

        // Get the value of y ( from 1 to 5)
        do {
            cout << "Player " << name << ", enter the column of the cell you want to choose:\n";
            cin >> column;
        } while (column < "1" || column > "5" || column.size() != 1);
        y = stoi(column) - 1;
    }
}


void Game3_Player::set_moves(int& moves) {
    n_moves = &moves;
}



class Game3_Random : public RandomPlayer<string> {
    static int* n_moves;
public:
    Game3_Random(string s, string n) : RandomPlayer<string>(s) {
        dimension = 5;
        name = n;
        srand(static_cast<unsigned int>(time(0)));
    }

    ~Game3_Random() {
        n_moves = nullptr;
        delete n_moves;
    }

    void getmove(int &x, int &y) override {
        if (*n_moves != 24){
            x = rand() % dimension;
            y = rand() % dimension;
        }
    }

    static void set_moves(int& moves) {
        n_moves = &moves;
    }
};

int* Game3_Random::n_moves = nullptr;

#endif //A2T2_3_4_GAME3_PLAYER_H
