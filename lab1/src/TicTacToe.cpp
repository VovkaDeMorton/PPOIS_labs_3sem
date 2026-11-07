#include "TicTacToe.h"

TicTacToe::TicTacToe()
    : board(3, std::vector<char>(3, ' ')),
      size(3),
      winLength(3),
      currentPlayer('X'),
      gameState(GameState::InProgress)
{
}

TicTacToe::TicTacToe(int size, int winLength)
    : board(size, std::vector<char>(size, ' ')),
      size(size),
      winLength(winLength),
      currentPlayer('X'),
      gameState(GameState::InProgress)
{
}

TicTacToe::TicTacToe(const TicTacToe& other)
    : board(other.board),
      size(other.size),
      winLength(other.winLength),
      currentPlayer(other.currentPlayer),
      gameState(other.gameState)
{
}

TicTacToe::~TicTacToe()
{
    // vector сам освобождает память — здесь ничего делать не нужно
}

int TicTacToe::getSize() const {
    return size;
}

int TicTacToe::getWinLength() const {
    return winLength;
}

char TicTacToe::getCurrentPlayer() const {
    return currentPlayer;
}

GameState TicTacToe::getState() const {
    return gameState;
}

bool TicTacToe::isGameOver() const {
    return gameState != GameState::InProgress;
}

char TicTacToe::getCell(int row, int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
    throw std::out_of_range("Cell coordinates out of range");
    }
    return board[row][col];
}

void TicTacToe::reset() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
    currentPlayer = 'X';
    gameState = GameState::InProgress;
}

bool TicTacToe::isBoardFull() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::isValidMove(int row, int col) const {
    if (gameState != GameState::InProgress) {
        return false;
    }
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false;
    }
    if (board[row][col] != ' ') {
        return false;
    }
    return true;
}

int TicTacToe::countInDirection(int row, int col, int dRow, int dCol) const {
    char symbol = board[row][col];
    int count = 0;
    int r = row;
    int c = col;
    
    while (r >= 0 && r < size && c >= 0 && c < size && board[r][c] == symbol) {
        count++;
        r += dRow;
        c += dCol;
    }
    
    return count;
}

bool TicTacToe::checkWin(int row, int col) const {
    int horizontal = countInDirection(row, col, 0, 1) 
                   + countInDirection(row, col, 0, -1) - 1;
    int vertical = countInDirection(row, col, 1, 0) 
                 + countInDirection(row, col, -1, 0) - 1;
    int diagonal1 = countInDirection(row, col, 1, 1) 
                  + countInDirection(row, col, -1, -1) - 1;
    int diagonal2 = countInDirection(row, col, 1, -1) 
                  + countInDirection(row, col, -1, 1) - 1;

    return horizontal >= winLength 
        || vertical >= winLength 
        || diagonal1 >= winLength 
        || diagonal2 >= winLength;
}

bool TicTacToe::makeMove(int row, int col) {
    if (!isValidMove(row, col)) {
        return false;
    }

    board[row][col] = currentPlayer;

    if (checkWin(row, col)) {
        if (currentPlayer == 'X') {
            gameState = GameState::XWins;
        } else {
            gameState = GameState::OWins;
        }
        return true;
    }

    if (isBoardFull()) {
        gameState = GameState::Draw;
        return true;
    }

    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    return true;
}

TicTacToe& TicTacToe::operator=(const TicTacToe& other) {
    if (this != &other) {
        board = other.board;
        size = other.size;
        winLength = other.winLength;
        currentPlayer = other.currentPlayer;
        gameState = other.gameState;
    }
    return *this;
}

bool TicTacToe::operator==(const TicTacToe& other) const {
    return board == other.board
        && size == other.size
        && winLength == other.winLength
        && currentPlayer == other.currentPlayer
        && gameState == other.gameState;
}

bool TicTacToe::operator!=(const TicTacToe& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const TicTacToe& game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            os << game.board[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, TicTacToe& game) {
    is >> game.size;
    is >> game.winLength;
    game.board = std::vector<std::vector<char>>(
        game.size, std::vector<char>(game.size, ' ')
    );
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            is >> game.board[i][j];
        }
    }
    game.currentPlayer = 'X';
    game.gameState = GameState::InProgress;
    return is;
}