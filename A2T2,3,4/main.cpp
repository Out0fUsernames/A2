#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
#include "Game3_Board.h"
#include "Game3_Player.h"
#include "Game6_Board.h"
#include "Game6_Player.h"
#include "Game7_Board.h"
#include "Game7_Player.h"
#include "Game8_Board.h"
#include "Game8_Player.h"
#include "PYRAMIC_XO.h"
#include "wordTic_tac_toe.h"
using namespace std;


int main() {
    // Keep playing until user chooses '7' (exit)
    while (true){
        string game_choice, player1_type, player2_type, player1_name = "Computer1", player2_name = "Computer2";

        // Get a number from 1 to 7 from the user
        do {
            cout << "\n\n1) Pyramid Tic-Tac-Toe\n2) Word Tic-Tac-Toe\n3) 5x5 Tic-Tac-Toe\n4) Misere Tic-Tac-Toe\n"
                    "5) 4x4 Tic-Tac-Toe\n6) Ultimate Tic-Tac-Toe\n7) Exit\nEnter the number of the game you want "
                    "to play or 7 to exit:\n\n";
            getline(cin, game_choice);
        } while (game_choice < "1" || game_choice > "7" || game_choice.size() != 1);

        // The user wants to exit
        if (game_choice == "7")
            return 0;

        // Get the type of player 1
        do {
            cout << "\n\nPlayer 1 type:\n1) Computer\n2) Human\n\n";
            getline(cin, player1_type);
        } while (player1_type != "1" && player1_type != "2");

        // Get the player's name
        if (player1_type == "2") {
            cout << "Player 1, what's your name?\n";
            getline(cin, player1_name);
        }

        // Get the type of player 2
        do {
            cout << "\n\nPlayer 2 type:\n1) Computer\n2) Human\n\n";
            getline(cin, player2_type);
        } while (player2_type != "1" && player2_type != "2");

        // Get the player's name
        if (player2_type == "2") {
            cout << "Player 2, what's your name?\n";
            getline(cin, player2_name);
        }

        // Pointer to the two players
        Player<string>* player1;
        Player<string>* player2;

        // Game 1
        if (game_choice == "1") {
            Player<char>* players[2];
            Board<char>* board = new Pyramic_XO_Board<char>();

            if (player1_type == "2")
                players[0] = new Pyramic_XO_Player<char>(player1_name, 'X');
            else
                players[0] = new Pyramic_XO_Random_Player<char>('X');

            if (player2_type == "2")
                players[1] = new Pyramic_XO_Player<char>(player2_name, 'O');
            else
                players[1] = new Pyramic_XO_Random_Player<char>('O');

            GameManager<char> game(board, players);
            game.run();

            delete board;
            for (auto & player : players) {
                delete player;
            }
        }
        // Game 2
        else if (game_choice == "2") {
            Player<char>* players[2];
            Board<char>* board = new X_O_Board<char>();

            if (player1_type == "2")
                players[0] = new X_O_Player<char>(player1_name, 'X');
            else
                players[0] = new X_O_Random_Player<char>('X');

            if (player2_type == "2")
                players[1] = new X_O_Player<char>(player2_name, 'O');
            else
                players[1] = new X_O_Random_Player<char>('O');

            GameManager<char> game(board, players);
            game.run();

            delete board;
            for (auto & player : players) {
                delete player;
            }
        }
        // Game 3
        else if (game_choice == "3") {
            // Board
            Game3_Board board;
            Board<string> *board_pointer = &board;
            Game3_Player::set_moves(board.get_moves());
            Game3_Random::set_moves(board.get_moves());

            // Players
            if (player1_type == "2")
                player1 = new Game3_Player(player1_name, "X");
            else
                player1 = new Game3_Random("X", player1_name);

            if (player2_type == "2")
                player2 = new Game3_Player(player2_name, "O");
            else
                player2 = new Game3_Random("O", player2_name);
            Player<string> *players[] = {player1, player2};

            // Manager
            GameManager manager(board_pointer, players);
            manager.run();

        }
        // Game 4
        else if (game_choice == "4") {
            // Board
            Game6_Board board;
            Board<string> *board_pointer = &board;

            // Players
            if (player1_type == "2")
                player1 = new Game6_Player(player1_name, "X", player2_name);
            else
                player1 = new Game6_Random("X", player2_name);

            if (player2_type == "2")
                player2 = new Game6_Player(player2_name, "O", player1_name);
            else
                player2 = new Game6_Random("O", player1_name);
            Player<string> *players[] = {player1, player2};

            // Manager
            GameManager manager(board_pointer, players);
            manager.run();
        }
        // Game 5
        else if (game_choice == "5") {
            // Board
            Game7_Board board;
            Board<string> *board_pointer = &board;

            // Players
            if (player1_type == "2")
                player1 = new Game7_Player(player1_name, "X", board_pointer);
            else
                player1 = new Game7_Random("X", player1_name, board_pointer);

            if (player2_type == "2")
                player2 = new Game7_Player(player2_name, "O", board_pointer);
            else
                player2 = new Game7_Random("O", player2_name, board_pointer);
            Player<string> *players[] = {player1, player2};

            // Manager
            GameManager manager(board_pointer, players);
            manager.run();
        }
        // Game 6
        else {
            // Board
            Main_Board board;
            Board<string> *board_pointer = &board;

            // Players
            if (player1_type == "2")
                player1 = new Game8_Player(player1_name, "X");
            else
                player1 = new Game8_Random("X", player1_name);

            if (player2_type == "2")
                player2 = new Game8_Player(player2_name, "O");
            else
                player2 = new Game8_Random("O", player2_name);
            Player<string> *players[] = {player1, player2};

            // Manager
            GameManager manager(board_pointer, players);
            manager.run();
        }

        // Free memory
        delete player1;
        delete player2;
    }
    return 0;
}
