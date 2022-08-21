#ifndef KNIGHTS_MOVE_H
#define KNIGHTS_MOVE_H

#pragma once

#include <vector>

struct GameCell {
    GameCell(const unsigned int r_val, const unsigned int c_val)
        : row(r_val), column(c_val) {}

    bool operator==(const GameCell& another_gc) const {
        if (row != another_gc.row) return false;
        if (column != another_gc.column) return false;
        return true;
    }

    unsigned int row;
    unsigned int column;
};

class KnightsMove {
public:
    explicit KnightsMove(const unsigned int new_side_size) :
        side_size(new_side_size), moves_done(0), game_in_progress(false), game_finished(false) {
        array_size = side_size * side_size;
    }

    // Нам не нужны копии объекта данного класса.
    KnightsMove(const KnightsMove& km) = delete;
    KnightsMove& operator=(const KnightsMove& km) = delete;

    ~KnightsMove() {
        moves_array.clear();
        moves_history.clear();
    }

    // Узнать, началась ли игра.
    inline bool game_is_in_progress() const { return game_in_progress; }

    // Узнать, прошел ли пользователь игру.
    inline bool game_is_finished() const { return game_finished; }

    // Начать игру.
    void start_game();

    // Узнать, сделан ли первый ход в игре.
    bool first_move_done() const;

    // Сбросить ход игры.
    void reject_game();

    // Сделать ход. Возвращаем true, если по переданным координатам удалось ход.
    bool make_move(const unsigned int row, const unsigned int column);

    // Узнать, возможен ли ход по переданным координатам поля.
    bool move_is_possible(const unsigned int row, const unsigned int column) const;

    // Получить набор из 8 максимально возможных ходов, относительно переданной клетки поля.
    void get_possible_moves(const GameCell gcell, std::vector<GameCell> &gc_vect) const;

    // Проверить, лежат ли переданные координаты в рамках игрового поля.
    bool check_bounds(const int row, const int column) const;

    // Узнать, использовано ли уже клекта по заданным координатам для хода.
    bool cell_is_marked(const unsigned int row, const unsigned int column) const;

    // Удалить заданное количество последних ходов. Переданное число не должно превышать кол-во уже сделанных.
    bool delete_moves(const size_t moves_number, std::vector<GameCell> &deleted_cells);

    // Узнать номер последнего хода.
    size_t get_moves_done() const { return moves_done; }

    // Получить ячейку последнего хода.
    inline GameCell get_last_move_cell() { return moves_history.at(moves_done-1);}

private:
    std::vector<size_t> moves_array; // Массив, представляющий игровое поле.
    std::vector<GameCell> moves_history; // Массив, в котором хранится вся история ходов по порядку.

    unsigned int side_size; // Кол-во клеток по одной стороне.
    size_t array_size; // Общее кол-во клеток для игры.

    size_t moves_done; // Кол-во сделанных ходов.

    bool game_in_progress; // Флаг, что игра началась.
    bool game_finished; // Флаг, что пользователь прошел игру.
};

#endif // KNIGHTS_MOVE_H
