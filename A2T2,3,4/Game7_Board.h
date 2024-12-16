#ifndef A2T2_3_4_GAME7_BOARD_H
#define A2T2_3_4_GAME7_BOARD_H
#include "BoardGame_Classes.h"

class Game7_Board : public Board<string> {
    bool token = false;
    string x_token = "0", y_token = "0";
    int current_x = 0, current_y = 0;
public:
    // Constructor and destructor
    Game7_Board();
    ~Game7_Board();

    // Class methods
    bool update_board(int x, int y, string symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    bool is_set(const string& symbol);
    void get_token(bool computer);
};

// Game7_Board constructor
Game7_Board::Game7_Board() {
    rows = 4;
    columns = 4;
    board = new string*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new string[columns];
    }
    // Initial places of tokens
    board[0][1] = board[0][3] = board[3][0] = board[3][2] = "X";
    board[0][0] = board[0][2] = board[3][1] = board[3][3] = "O";
}

// Game7_Board destructor
Game7_Board::~Game7_Board() {
    // Free memory to avoid memory leak
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

// Update the board if the move is valid
bool Game7_Board::update_board(int x, int y, string symbol) {
    bool computer = false;
    if (symbol.size() == 2) {
        computer = true;
    }
    if (!token) {
        get_token(computer);
        token = true;
        return true;
    }
    else {
        // Place the symbol in this cell if it's not taken
        if (board[x][y].empty() &&
            ((abs(current_x - x) == 1 && current_y - y == 0) || (abs(current_y - y) == 1) && current_x - x == 0)) {
            board[x][y] = symbol;
            board[current_x][current_y] = "";
            n_moves++;  // Increment the number of moves
            token = false;
            return true;
        }
        return false;
    }
}

// Display current state
void Game7_Board::display_board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Print the position of the cell if it's not chosen '(row number, column number)'
            if (board[i][j].empty()) {
                cout << "(" << i + 1 << ", " << j + 1 << ") ";
                // Vertical separator
                if (j != 3) {
                    cout << "| ";
                }
            }
                // Print 'X' or 'O'
            else {
                cout << "   " << board[i][j] << "   ";
                // Vertical separator
                if (j != 3) {
                    cout << "| ";
                }
            }
        }
        // Horizontal separator
        cout << endl << (i != 3 ? string(35, '_') : "\n") << endl;
    }
}

bool Game7_Board::is_win() {
    string symbol = n_moves % 2 ? "X" : "O";
    return is_set(symbol);
}

bool Game7_Board::is_draw() {
    return false;
}

bool Game7_Board::game_is_over() {
    return false;
}

bool Game7_Board::is_set(const string& symbol) {
    for (int i = 0; i < rows; ++i) {
        // Horizontal or vertical set
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||
            (board[i][1] == symbol && board[i][2] == symbol && board[i][3] == symbol) ||
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) ||
            (board[1][i] == symbol && board[2][i] == symbol && board[3][i] == symbol))
            return true;

        for (int j = 0; j < columns; ++j) {
            // Make sure that indices aren't out of bounds
            if (i + 1 < rows && i + 2 < rows && j - 1 >= 0 && j - 2 >= 0) {
                // Diagonal(/) set
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                    return true;
                }
            }

            // Make sure that indices aren't out of bounds
            if (i + 1 < rows && i + 2 < rows && j + 1 < columns && j + 2 < columns) {
                // Diagonal(\) set
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Game7_Board::get_token(bool computer) {
    string symbol = (n_moves % 2 ? "O" : "X");

    if (!computer){
        // Get the value of x (from 1 to 4)
        do {
            cout << "Enter the row of the token you want to choose:\n";
            cin >> x_token;
        } while (x_token < "1" || x_token > "4");

        // Get the value of y (from 1 to 4)
        do {
            cout << "Enter the column of the token you want to choose:\n";
            cin >> y_token;
        } while (y_token < "1" || y_token > "4");

        current_x = stoi(x_token) - 1;
        current_y = stoi(y_token) - 1;
    }
    else {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 3);

        current_x = dist(gen);  // Random number between 0 and 2
        current_y = dist(gen);
    }
    if (board[current_x][current_y] != symbol.substr(0, 1) ||
        (!board[current_x][min(current_y + 1, 3)].empty() && !board[current_x][max(current_y - 1, 0)].empty() &&
         !board[min(current_x + 1, 3)][current_y].empty() && !board[max(current_x - 1, 0)][current_y].empty()))
        get_token(computer);
}


#endif //A2T2_3_4_GAME7_BOARD_H
