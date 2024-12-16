#ifndef A2T2_3_4_GAME8_BOARD_H
#define A2T2_3_4_GAME8_BOARD_H
#include <utility>

#include "BoardGame_Classes.h"

class Sub_Board : public Board<string> {
protected:
    string winner = "";
public:
    // Constructor and destructor
    Sub_Board();

    // Class methods
    bool update_board(int x, int y, string symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_set(const string& symbol);
    string get_winner();
};

Sub_Board::Sub_Board() {
    rows = 3;
    columns = 3;

    board = new string*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new string[columns];
    }
}


bool Sub_Board::update_board(int x, int y, string symbol) {
    // Place the symbol in this cell if it's not taken
    if (board[x][y].empty()) {
        board[x][y] = symbol;
        is_win();
        n_moves++;  // Increment the number of moves
        return true;
    }
    return false;
}

void Sub_Board::display_board() {}

bool Sub_Board::is_win() {
    string symbol = n_moves % 2 ? "X" : "O";
    if (is_set(symbol)) {
        winner = symbol;
        return true;
    }
    return false;
}

bool Sub_Board::is_draw() {
    return n_moves == 9;
}

bool Sub_Board::game_is_over() {return false;}

bool Sub_Board::is_set(const string &symbol) {
    for (int i = 0; i < rows; ++i) {
        // Horizontal or vertical set
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol))
            return true;
    }

    // Diagonals
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol))
        return true;

    return false;
}

string Sub_Board::get_winner() {
    return winner;
}


class Main_Board : public Board<string> {
    Sub_Board sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8, sub9;
    Sub_Board boards[9] = {sub1, sub2, sub3, sub4, sub5, sub6, sub7, sub8, sub9};
public:
    // Constructor and destructor
    Main_Board();
    ~Main_Board();

    // Class methods
    bool update_board(int x, int y, string symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_set(const string& symbol);
};

Main_Board::Main_Board() {
    rows = 9;
    columns = 9;

    board = new string*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new string[columns];
    }
}

Main_Board::~Main_Board() {
    // Free memory to avoid memory leak
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

bool Main_Board::update_board(int x, int y, string symbol) {
    // Place the symbol in this cell if it's not taken
    if (board[x][y].empty()) {
        int sub_num = (3 * (x / 3)) + (y / 3);
        int sub_x = (x % 3);
        int sub_y = (y % 3);
        boards[sub_num].update_board(sub_x, sub_y, symbol);
        board[x][y] = symbol;
        if (boards[sub_num].is_win()) {
            int s_row = 3 * (sub_num / 3);
            int s_col = 3 * (sub_num % 3);
            for (int i = s_row; i < s_row + 3; ++i) {
                for (int j = s_col; j < s_col + 3; j++) {
                    if (board[i][j].empty()) {
                        board[i][j] = ".";
                        n_moves++;
                    }
                }
            }
        }
        n_moves++;  // Increment the number of moves
        return true;
    }
    return false;
}

void Main_Board::display_board() {
    cout << endl << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int sub_num = (3 * (i / 3)) + (j / 3);
            if (j % 3 == 0 && j)
                cout << "||";
            // Print the position of the cell if it's not chosen '(row number, column number)'
            if (board[i][j].empty()) {
                cout << " (" << i + 1 << ", " << j + 1 << ") ";
                // Vertical separator
                if (j != 8) {
                    cout << "|";
                }
            }
                // Print 'X' or 'O'
            else {
                cout << "    " << board[i][j] << "   ";
                // Vertical separator
                if (j != 8) {
                    cout << "|";
                }
            }
        }
        cout << endl << string(85, '_') << endl;
        if (i == 2 || i == 5)
            cout << string(85, '_') << endl << string(85, '_') << endl;
    }
}

bool Main_Board::is_win() {
    string symbol = n_moves % 2 ? "X" : "O";
    return is_set(symbol);
}

bool Main_Board::is_draw() {
    return n_moves == 81;
}

bool Main_Board::game_is_over() {
    return false;
}

bool Main_Board::is_set(const string &symbol) {
    for (int i = 0; i < 9; i+=3) {
        // Horizontal set
        if (boards[i].get_winner() == symbol && boards[i+1].get_winner() == symbol && boards[i + 2].get_winner() == symbol)
            return true;
    }

    for (int i = 0; i < 3; ++i) {
        if (boards[i].get_winner() == symbol && boards[i + 3].get_winner() == symbol && boards[i + 6].get_winner() == symbol)
            return true;
    }

    // Diagonals
    if ((boards[0].get_winner() == symbol && boards[4].get_winner() == symbol && boards[8].get_winner() == symbol) ||
        (boards[2].get_winner() == symbol && boards[4].get_winner() == symbol && boards[6].get_winner() == symbol))
        return true;

    return false;
}

#endif //A2T2_3_4_GAME8_BOARD_H
