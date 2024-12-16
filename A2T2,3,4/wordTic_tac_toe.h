#ifndef _wordTic_tac_toe_H
#define _wordTic_tac_toe_H

#include "BoardGame_Classes.h"
#include <set>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> // for toupper()

using namespace std;

// Template class for Tic Tac Toe board with word validation
template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

    set<string> validWords; // Set to store valid words
    void loadValidWords(); // Load valid words from file
    bool isValidWord(const string& word);

private:
    int n_moves; // To track the number of moves
};

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update the board with a move
template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && (this->board[x][y] == 0 || mark != 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = mark;
        }

        // Check for valid word formed
        if (is_win()) {
            cout << "Valid word formed!\n";
            return true;
        }
        return true;
    }
    return false;
}

// Display the board
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check if there is a winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        string rowWord = "", reverseRowWord = "";
        for (int j = 0; j < this->columns; j++) {
            rowWord += this->board[i][j];
            reverseRowWord = this->board[i][j] + reverseRowWord;
        }
        if (isValidWord(rowWord) || isValidWord(reverseRowWord)) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        string colWord = "", reverseColWord = "";
        for (int i = 0; i < this->rows; i++) {
            colWord += this->board[i][j];
            reverseColWord = this->board[i][j] + reverseColWord;
        }
        if (isValidWord(colWord) || isValidWord(reverseColWord)) {
            return true;
        }
    }

    // Check diagonals
    string diag1Word = "", reverseDiag1Word = "";
    for (int i = 0; i < this->rows; i++) {
        diag1Word += this->board[i][i];
        reverseDiag1Word = this->board[i][i] + reverseDiag1Word;
    }
    if (isValidWord(diag1Word) || isValidWord(reverseDiag1Word)) {
        return true;
    }

    string diag2Word = "", reverseDiag2Word = "";
    for (int i = 0; i < this->rows; i++) {
        diag2Word += this->board[i][this->columns - i - 1];
        reverseDiag2Word = this->board[i][this->columns - i - 1] + reverseDiag2Word;
    }
    if (isValidWord(diag2Word) || isValidWord(reverseDiag2Word)) {
        return true;
    }

    return false;
}

// Check if the game is a draw
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Load valid words from file
template <typename T>
void X_O_Board<T>::loadValidWords() {
    string filename = "dic.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        this->validWords.insert(word); // Insert into set
    }

    file.close();
}

// Check if the word is valid
template <typename T>
bool X_O_Board<T>::isValidWord(const string& word) {
    return validWords.find(word) != validWords.end();
}

// ----------------------------------------------------------

// X_O_Player class
template <typename T>
class X_O_Player : public Player<T> {
private:
    T currentSymbol; // To store the symbol

public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
    T getsymbol();
};

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {
    this->currentSymbol = symbol;
}

// Override the getsymbol() method to return the dynamically chosen symbol (currentSymbol).
template <typename T>
T X_O_Player<T>::getsymbol() {
    return this->currentSymbol;
}

// Get move from the player
template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "Enter the letter you want for this move: ";
    cin >> this->currentSymbol;
    this->currentSymbol = toupper(this->currentSymbol);
    while (!isalpha(this->currentSymbol)) {
        cout << "Invalid symbol! Please use a letter. Try again.\n";
        cout << "Enter the letter you want for this move: ";
        cin >> this->currentSymbol;
        this->currentSymbol = toupper(this->currentSymbol);
    }
    this->symbol = currentSymbol;
}

// ----------------------------------------------------------

// X_O_Random_Player class
template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
private:
    T currentSymbol; // To store the symbol

public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
    T getsymbol();
};

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Get move from the random player
template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension; // Random number between 0 and 2
    y = rand() % this->dimension;
    this->currentSymbol = 'A' + (rand() % 26);
    this->symbol = currentSymbol;
}

// Return the symbol of the random player
template <typename T>
T X_O_Random_Player<T>::getsymbol() {
    return this->currentSymbol;
}

#endif //_wordTic_tac_toe_H
