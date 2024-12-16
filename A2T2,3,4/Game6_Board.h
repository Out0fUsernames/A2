#ifndef A2T2_3_4_GAME6_BOARD_H
#define A2T2_3_4_GAME6_BOARD_H
#include "BoardGame_Classes.h"

class Game6_Board : public Board<string> {
public:
    // Constructor and destructor
    Game6_Board();
    ~Game6_Board();

    // Class methods
    bool update_board(int x, int y, string symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_set(const string& symbol);
};

// Game6_Board constructor
Game6_Board::Game6_Board() {
    rows = 3;
    columns = 3;
    board = new string*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new string[columns];
    }
}

// Game6_Board destructor
Game6_Board::~Game6_Board() {
    // Free memory to avoid memory leak
    for (int i = 0; i < 3; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

// Update the board if the move is valid
bool Game6_Board::update_board(int x, int y, string symbol) {
    // Place the symbol in this cell if it's not taken
    if (board[x][y].empty()) {
        board[x][y] = symbol;
        n_moves++;  // Increment the number of moves
        return true;
    }
    return false;
}

// Display current state
void Game6_Board::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Print the position of the cell if it's not chosen '(row number, column number)'
            if (board[i][j].empty()) {
                cout << "(" << i + 1 << ", " << j + 1 << ") ";
                // Vertical separator
                if (j != 2) {
                    cout << "| ";
                }
            }
            // Print 'X' or 'O'
            else {
                cout << "   " << board[i][j] << "   ";
                // Vertical separator
                if (j != 2) {
                    cout << "| ";
                }
            }
        }
        // Horizontal separator
        cout << endl << (i != 2 ? string(25, '_') : "\n") << endl;
    }
}

bool Game6_Board::is_win() {
    string symbol = n_moves % 2 ? "X" : "O";
    return is_set(symbol);
}

bool Game6_Board::is_draw() {
    return n_moves == 9 && !is_win();
}

bool Game6_Board::game_is_over() {
    return is_win() || n_moves == 9;
}

bool Game6_Board::is_set(const string& symbol) {
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

#endif //A2T2_3_4_GAME6_BOARD_H
