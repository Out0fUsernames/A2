#ifndef A2T2_3_4_GAME3_BOARD_H
#define A2T2_3_4_GAME3_BOARD_H
#include "BoardGame_Classes.h"

// Game 3 Board
class Game3_Board : public Board<string> {
public:
    // Constructor and destructor
    Game3_Board();
    ~Game3_Board();

    // Class methods
    bool update_board(int x, int y, string symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int calculate_sets(const string& symbol);
    int& get_moves();
};

// Game3_Board constructor
Game3_Board::Game3_Board() {
    rows = 5;
    columns = 5;
    board = new string*[rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new string[columns];
    }
}

// Game3_Board destructor
Game3_Board::~Game3_Board() {
    // Free memory to avoid memory leak
    for (int i = 0; i < 5; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

// Update the board if the move is valid
bool Game3_Board::update_board(int x, int y, string symbol) {
    // Place the symbol in this cell if it's not taken
    if (board[x][y].empty()) {
        board[x][y] = symbol;
        n_moves++;  // Increment the number of moves
        return true;
    }
    // No moves left and player 1 wins
    else if (n_moves == 24) {
        n_moves++;
        return true;
    }
    return false;  // Move is invalid
}

// Display current state
void Game3_Board::display_board() {
    if (n_moves != 25){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                // Print the position of the cell if it's not chosen '(row number, column number)'
                if (board[i][j].empty()) {
                    cout << "(" << i + 1 << ", " << j + 1 << ") ";
                    // Vertical separator
                    if (j != 4) {
                        cout << "| ";
                    }
                }
                // Print 'X' or 'O'
                else {
                    cout << "   " << board[i][j] << "   ";
                    // Vertical separator
                    if (j != 4) {
                        cout << "| ";
                    }
                }
            }
            // Horizontal separator
            cout << endl << (i != 4 ? string(45, '_') : "\n") << endl;
        }
    }
}

// Returns true if there is a winner
bool Game3_Board::is_win() {
    return (n_moves == 24 && calculate_sets("X") < calculate_sets("O"))   // Player 2 wins
        || (n_moves == 25 && calculate_sets("X") > calculate_sets("O"));  // Player 1 wins
}

// Returns true if it's a draw (sets are equal)
bool Game3_Board::is_draw() {
    return n_moves == 24 && calculate_sets("X") == calculate_sets("O");
}

// Returns true if the game is over
bool Game3_Board::game_is_over() {
    return (n_moves == 24 && (is_win() || is_draw())) || n_moves == 25;
}

// Returns the number of sets
int Game3_Board::calculate_sets(const string& symbol) {
    int sets = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Make sure that indices aren't out of bounds
            if (i + 1 < rows && i + 2 < rows && j - 1 >= 0 && j - 2 >= 0) {
                // Diagonal(/) set
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                    sets++;
                }
            }

            // Make sure that indices aren't out of bounds
            if (i + 1 < rows && i + 2 < rows && j + 1 < columns && j + 2 < columns) {
                // Diagonal(\) set
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                    sets++;
                }
            }

            // Make sure that indices aren't out of bounds
            if (j + 1 < columns && j + 2 < columns) {
                // Horizontal set
                if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                    sets++;
                }
            }

            // Make sure that indices aren't out of bounds
            if (i + 1 < rows && i + 2 < rows && j - 1 >= 0 && j - 2 >= 0) {
                // Vertical set
                if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                    sets++;
                }
            }
        }

    }
    return sets;
}

// n_moves getter
int& Game3_Board::get_moves() {
    return n_moves;
}


#endif //A2T2_3_4_GAME3_BOARD_H
