#include <gtest/gtest.h>
#include "TicTacToe.h"

// Тест 1: Проверка конструктора по умолчанию
TEST(TicTacToeTest, DefaultConstructor) {
    TicTacToe game;
    
    // EXPECT_EQ(что_получили, что_ожидали)
    EXPECT_EQ(game.getSize(), 3);
    EXPECT_EQ(game.getWinLength(), 3);
    EXPECT_EQ(game.getCurrentPlayer(), 'X');
    EXPECT_EQ(game.getState(), GameState::InProgress);
    EXPECT_FALSE(game.isGameOver()); // Игра еще не закончена
}

// Тест 2: Проверка конструктора с параметрами
TEST(TicTacToeTest, ParamConstructor) {
    TicTacToe game(5, 4);
    
    EXPECT_EQ(game.getSize(), 5);
    EXPECT_EQ(game.getWinLength(), 4);
}

// Тест 3: Проверка валидного хода
TEST(TicTacToeTest, MakeValidMove) {
    TicTacToe game;
    
    // Делаем ход в центр
    EXPECT_TRUE(game.makeMove(1, 1));
    
    // Проверяем, что там теперь стоит X, а ход перешел к O
    EXPECT_EQ(game.getCell(1, 1), 'X');
    EXPECT_EQ(game.getCurrentPlayer(), 'O');
}

// Тест 4: Проверка победы по горизонтали
TEST(TicTacToeTest, WinHorizontal) {
    TicTacToe game;
    game.makeMove(0, 0); // X
    game.makeMove(1, 0); // O
    game.makeMove(0, 1); // X
    game.makeMove(1, 1); // O
    game.makeMove(0, 2); // X выигрывает (верхняя строка)

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getState(), GameState::XWins);
}

// Тест 5: Проверка ничьей (заполняем всё поле)
TEST(TicTacToeTest, DrawGame) {
    TicTacToe game;
    // Хитрый порядок ходов, чтобы никто не выиграл
    game.makeMove(0, 0); // X
    game.makeMove(0, 1); // O
    game.makeMove(0, 2); // X
    game.makeMove(1, 1); // O
    game.makeMove(1, 0); // X
    game.makeMove(2, 0); // O
    game.makeMove(1, 2); // X
    game.makeMove(2, 2); // O
    game.makeMove(2, 1); // X (поле заполнено)

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getState(), GameState::Draw);
}

// Тест 6: Ход после окончания игры должен быть невозможен
TEST(TicTacToeTest, CannotMoveAfterWin) {
    TicTacToe game(3, 2); // Поле 3х3, для победы нужно 2 в ряд
    game.makeMove(0, 0); // X
    game.makeMove(1, 0); // O
    game.makeMove(0, 1); // X (победа!)

    // Пытаемся сходить еще раз
    EXPECT_FALSE(game.makeMove(1, 1));
}

// Тест 7: Проверка исключения (выход за границы поля)
TEST(TicTacToeTest, OutOfBoundsException) {
    TicTacToe game;
    // Проверяем, что вызов getCell(5, 5) вызовет ошибку std::out_of_range
    EXPECT_THROW(game.getCell(5, 5), std::out_of_range);
}

// Тест 8: Проверка оператора равенства (==)
TEST(TicTacToeTest, OperatorEquality) {
    TicTacToe game1;
    TicTacToe game2;
    
    EXPECT_TRUE(game1 == game2); // Две пустые игры одинаковы
    
    game1.makeMove(1, 1);
    EXPECT_FALSE(game1 == game2); // После хода они разные
}

// Тест 9: Проверка оператора присваивания (=)
TEST(TicTacToeTest, OperatorAssignment) {
    TicTacToe game1;
    game1.makeMove(0, 0); // Сделали ход
    
    TicTacToe game2;
    game2 = game1; // Скопировали игру1 в игру2
    
    EXPECT_TRUE(game1 == game2); // Теперь они одинаковые
    EXPECT_EQ(game2.getCell(0, 0), 'X'); // Ход скопировался
}

// Тест 10: Проверка сброса игры (reset)
TEST(TicTacToeTest, ResetGame) {
    TicTacToe game;
    game.makeMove(0, 0);
    EXPECT_EQ(game.getCell(0, 0), 'X');
    
    game.reset();
    EXPECT_EQ(game.getCell(0, 0), ' '); // Поле очистилось
    EXPECT_EQ(game.getCurrentPlayer(), 'X'); // Ход снова у X
    EXPECT_FALSE(game.isGameOver());
}

// Тест 11: Победа по вертикали
TEST(TicTacToeTest, WinVertical) {
    TicTacToe game;
    game.makeMove(0, 0); // X
    game.makeMove(0, 1); // O
    game.makeMove(1, 0); // X
    game.makeMove(1, 1); // O
    game.makeMove(2, 0); // X (победа)

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getState(), GameState::XWins);
}

// Тест 12: Победа по главной диагонали
TEST(TicTacToeTest, WinDiagonal1) {
    TicTacToe game;
    game.makeMove(0, 0); // X
    game.makeMove(0, 1); // O
    game.makeMove(1, 1); // X
    game.makeMove(0, 2); // O
    game.makeMove(2, 2); // X (победа)

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getState(), GameState::XWins);
}

// Тест 13: Победа по побочной диагонали
TEST(TicTacToeTest, WinDiagonal2) {
    TicTacToe game;
    game.makeMove(0, 2); // X
    game.makeMove(0, 0); // O
    game.makeMove(1, 1); // X
    game.makeMove(0, 1); // O
    game.makeMove(2, 0); // X (победа)

    EXPECT_TRUE(game.isGameOver());
    EXPECT_EQ(game.getState(), GameState::XWins);
}

// Тест 14: Конструктор копирования
TEST(TicTacToeTest, CopyConstructor) {
    TicTacToe game1;
    game1.makeMove(1, 1); // Ход X
    
    TicTacToe game2 = game1; // Вызов конструктора копирования
    
    EXPECT_EQ(game2.getCell(1, 1), 'X');
    EXPECT_TRUE(game1 == game2);
}

// Тест 15: Оператор вывода в поток (<<)
TEST(TicTacToeTest, StreamOutput) {
    TicTacToe game;
    game.makeMove(0, 0);
    
    std::ostringstream oss;
    oss << game; // Вызываем наш operator<<
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find('X'), std::string::npos); // В выводе есть 'X'
}

// Тест 16: Оператор ввода из потока (>>)
TEST(TicTacToeTest, StreamInput) {
    std::istringstream iss("3 3 X O X O X O X O");
    TicTacToe game;
    
    iss >> game; // Вызываем наш operator>>
    
    EXPECT_EQ(game.getSize(), 3);
    EXPECT_EQ(game.getWinLength(), 3);
    EXPECT_EQ(game.getCell(0, 0), 'X');
}