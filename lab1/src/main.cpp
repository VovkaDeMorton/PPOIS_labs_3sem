#include <iostream>
#include <stdexcept>
#include "TicTacToe.h"

void printMenu() {
    std::cout << "\n=== Tic-Tac-Toe ===\n";
    std::cout << "1. New game\n";
    std::cout << "2. Make move\n";
    std::cout << "3. Show board\n";
    std::cout << "4. Current player\n";
    std::cout << "5. Game status\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

void handleNewGame(TicTacToe& game) {
    int size, winLength;
    std::cout << "Board size (default 3): ";
    std::cin >> size;
    std::cout << "Win length (default 3): ";
    std::cin >> winLength;
    game = TicTacToe(size, winLength);
    std::cout << "Game created. Board " << size << "x" << size << ".\n";
}

void handleMove(TicTacToe& game) {
    int row, col;
    std::cout << "Enter row and column (space separated): ";
    std::cin >> row >> col;

    if (game.makeMove(row, col)) {
        std::cout << game;
    } else {
        std::cout << "Move not possible.\n";
    }
}

void handleShowBoard(const TicTacToe& game) {
    std::cout << game;
}

void handleCurrentPlayer(const TicTacToe& game) {
    std::cout << "Current player: " << game.getCurrentPlayer() << '\n';
}

void handleStatus(const TicTacToe& game) {
    switch (game.getState()) {
        case GameState::InProgress:
            std::cout << "Game in progress.\n";
            break;
        case GameState::XWins:
            std::cout << "X wins!\n";
            break;
        case GameState::OWins:
            std::cout << "O wins!\n";
            break;
        case GameState::Draw:
            std::cout << "Draw.\n";
            break;
    }
}

int main() {
    TicTacToe game;
    int choice = -1;

    std::cout << "Welcome to the game!\n";

    while (choice != 0) {
        printMenu();
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: handleNewGame(game); break;
                case 2: handleMove(game); break;
                case 3: handleShowBoard(game); break;
                case 4: handleCurrentPlayer(game); break;
                case 5: handleStatus(game); break;
                case 0: std::cout << "Exit.\n"; break;
                default: std::cout << "Invalid choice.\n"; break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}