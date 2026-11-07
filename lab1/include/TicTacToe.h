#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * @brief Состояние игры в крестики-нолики.
 * 
 * Определяет, чем сейчас занята игра: идёт партия, кто-то победил или ничья.
 */
enum class GameState {
    InProgress,   ///< Игра идёт, ходы возможны
    XWins,        ///< Победил игрок X
    OWins,        ///< Победил игрок O
    Draw          ///< Ничья, поле заполнено, победителя нет
};

/**
 * @brief Класс игры «Крестики-нолики» на поле произвольного размера.
 * 
 * Инкапсулирует игровое поле, текущего игрока и состояние партии.
 * Не знает ничего о пользовательском интерфейсе — только игровая логика.
 */
class TicTacToe {
private:
    std::vector<std::vector<char>> board;  ///< Игровое поле (сетка символов)
    int size;                              ///< Размер поля (3, 5, 10...)
    int winLength;                         ///< Сколько фигур в ряд нужно для победы
    char currentPlayer;                    ///< Чей сейчас ход ('X' или 'O')
    GameState gameState;                   ///< Текущее состояние игры

    /**
     * @brief Проверяет, можно ли сделать ход в клетку (row, col).
     * @param row Строка клетки.
     * @param col Столбец клетки.
     * @return true, если клетка в пределах поля, пуста и игра не закончена.
     */
    bool isValidMove(int row, int col) const;

    /**
     * @brief Проверяет, победил ли игрок после хода в клетку (row, col).
     * @param row Строка последнего хода.
     * @param col Столбец последнего хода.
     * @return true, если собрана линия нужной длины.
     */
    bool checkWin(int row, int col) const;

    /**
     * @brief Считает фигуры текущего игрока в одном направлении.
     * @param row Начальная строка.
     * @param col Начальный столбец.
     * @param dRow Сдвиг по строкам (-1, 0 или 1).
     * @param dCol Сдвиг по столбцам (-1, 0 или 1).
     * @return Количество фигур подряд в указанном направлении.
     */
    int countInDirection(int row, int col, int dRow, int dCol) const;

    /**
     * @brief Проверяет, заполнено ли всё поле.
     * @return true, если пустых клеток нет.
     */
    bool isBoardFull() const;

public:
    /**
     * @brief Конструктор по умолчанию.
     * Создаёт игру на поле 3x3 с победой при 3 в ряд.
     */
    TicTacToe();

    /**
     * @brief Конструктор с параметрами.
     * @param size Размер поля.
     * @param winLength Сколько фигур в ряд нужно для победы.
     */
    TicTacToe(int size, int winLength);

    /**
     * @brief Конструктор копирования.
     * @param other Игра, с которой снимается копия.
     */
    TicTacToe(const TicTacToe& other);

    /**
     * @brief Деструктор.
     */
    ~TicTacToe();

    /**
     * @brief Оператор присваивания копированием.
     * @param other Игра-источник.
     * @return Ссылка на текущий объект.
     */
    TicTacToe& operator=(const TicTacToe& other);

    /**
     * @brief Оператор сравнения на равенство.
     * @param other Игра для сравнения.
     * @return true, если все поля двух игр совпадают.
     */
    bool operator==(const TicTacToe& other) const;

    /**
     * @brief Оператор сравнения на неравенство.
     * @param other Игра для сравнения.
     * @return true, если игры различаются.
     */
    bool operator!=(const TicTacToe& other) const;

    /**
     * @brief Оператор вывода игры в поток.
     * @param os Поток вывода.
     * @param game Игра для вывода.
     * @return Ссылка на поток.
     */
    friend std::ostream& operator<<(std::ostream& os, const TicTacToe& game);

    /**
     * @brief Оператор ввода игры из потока.
     * @param is Поток ввода.
     * @param game Игра, в которую считывается состояние.
     * @return Ссылка на поток.
     */
    friend std::istream& operator>>(std::istream& is, TicTacToe& game);

    /**
     * @brief Делает ход текущего игрока в клетку (row, col).
     * @param row Строка клетки.
     * @param col Столбец клетки.
     * @return true, если ход сделан; false, если ход невозможен.
     */
    bool makeMove(int row, int col);

    /**
     * @brief Сбрасывает игру в начальное состояние.
     * Поле очищается, ход снова у X.
     */
    void reset();

    /**
     * @brief Проверяет, закончена ли игра.
     * @return true, если есть победитель или ничья.
     */
    bool isGameOver() const;

    /**
     * @brief Возвращает текущее состояние игры.
     * @return Одно из значений GameState.
     */
    GameState getState() const;

    /**
     * @brief Возвращает символ текущего игрока.
     * @return 'X' или 'O'.
     */
    char getCurrentPlayer() const;

    /**
     * @brief Возвращает содержимое клетки.
     * @param row Строка клетки.
     * @param col Столбец клетки.
     * @return 'X', 'O' или ' '.
     * @throws std::out_of_range если координаты вне поля.
     */
    char getCell(int row, int col) const;

    /**
     * @brief Возвращает размер игрового поля.
     * @return Размер поля (например, 3 для 3x3).
     */
    int getSize() const;

    /**
     * @brief Возвращает длину линии для победы.
     * @return Сколько фигур в ряд нужно, чтобы победить.
     */
    int getWinLength() const;
};

#endif