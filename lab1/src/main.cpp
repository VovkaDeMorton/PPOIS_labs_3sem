#include <iostream>
#include <stdexcept>
#include "TicTacToe.h"
#include "PostMachine.h"

// ==========================================
// ЛОГИКА КРЕСТИКОВ-НОЛИКОВ
// ==========================================
void printMenu() {
    std::cout << "\n=== Tic-Tac-Toe ===\n";
    std::cout << "1. New game\n";
    std::cout << "2. Make move\n";
    std::cout << "3. Show board\n";
    std::cout << "4. Current player\n";
    std::cout << "5. Game status\n";
    std::cout << "0. Back to Main Menu\n"; // Изменили текст
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
        case GameState::InProgress: std::cout << "Game in progress.\n"; break;
        case GameState::XWins:      std::cout << "X wins!\n"; break;
        case GameState::OWins:      std::cout << "O wins!\n"; break;
        case GameState::Draw:       std::cout << "Draw.\n"; break;
    }
}

void runTicTacToe() {
    TicTacToe game;
    int choice = -1;
    std::cout << "Welcome to Tic-Tac-Toe!\n";
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
                case 0: std::cout << "Returning to Main Menu.\n"; break;
                default: std::cout << "Invalid choice.\n"; break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}

// ==========================================
// ЛОГИКА МАШИНЫ ПОСТА
// ==========================================
void runPostMachine() {
    PostMachine pm;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Post Machine ===\n";
        std::cout << "Tape: " << pm << "\n";
        std::cout << "1. Move Left\n";
        std::cout << "2. Move Right\n";
        std::cout << "3. Write 1\n";
        std::cout << "4. Write 0\n";
        std::cout << "5. Halt Machine\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: pm.moveLeft(); break;
            case 2: pm.moveRight(); break;
            case 3: pm.write(1); break;
            case 4: pm.write(0); break;
            case 5: pm.halt(); break;
            case 0: std::cout << "Returning to Main Menu.\n"; break;
            default: std::cout << "Invalid choice.\n"; break;
        }
    }
}

// ==========================================
// ГЛАВНОЕ МЕНЮ
// ==========================================
int main() {
    int mainChoice = -1;
    while (mainChoice != 0) {
        std::cout << "\n=== MAIN MENU ===\n";
        std::cout << "1. Play Tic-Tac-Toe\n";
        std::cout << "2. Test Post Machine\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> mainChoice;
        
        if (mainChoice == 1) {
            runTicTacToe();
        } else if (mainChoice == 2) {
            runPostMachine();
        } else if (mainChoice == 0) {
            std::cout << "Exiting program. Goodbye!\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
    return 0;
}