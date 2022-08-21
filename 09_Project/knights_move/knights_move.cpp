#include "knights_move.h"

#include <algorithm>

// Начать игру.
void KnightsMove::start_game()
{
    moves_array.reserve(array_size);
    for(size_t i = 0; i < array_size; ++i) {
        moves_array.push_back(0);
    }

    moves_history.reserve(array_size);

    game_in_progress = true;
}

// Сбросить ход игры.
void KnightsMove::reject_game()
{
    moves_array.clear();
    moves_history.clear();
    moves_done = 0;
    game_in_progress = false;
    game_finished = false;
}

// Узнать, сделан ли первый ход в игре.
bool KnightsMove::first_move_done() const
{
    return (moves_done == 0) ? false : true;
}

// Сделать ход. Возвращаем true, если по переданным координатам возможен ход.
bool KnightsMove::make_move(const unsigned int row, const unsigned int column)
{
    if ( !move_is_possible(row, column)) {
        return false;
    }

    // Рассчет позиции внутри массива, представляющего игровое поле.
    size_t vector_position = static_cast<size_t>(row * side_size + column);

    ++moves_done; // Увеличиваем счетчик сделанных ходов.
    moves_array[vector_position] = moves_done;
    moves_history.push_back(GameCell(row, column));

    // Проверка, был ли это последний ход на поле.
    if (moves_done == array_size) {
        game_in_progress = false;
        game_finished = true;
    }

    return true;
}

// Узнать, возможен ли ход по переданным координатам поля.
bool KnightsMove::move_is_possible(const unsigned int row, const unsigned int column) const
{
    // Проверка на корректность параметров.
    if ( (row >= side_size) || (column >= side_size) ) {
        return false;
    }

    size_t vector_position = static_cast<size_t>(row * side_size + column);
    if (vector_position >= array_size) { // По сути эта проверка не нужна...
        return false;
    }

    // Это первый ход. Можно кликнуть в любую клетку.
    if ( moves_done == 0 ) {
        return true;
    }

    // Проверка, возможен ли ход по переданным координатам относительно клетки последнего хода.
    std::vector<GameCell> possible_moves;
    possible_moves.reserve(8);

    // Получаем набор возможных ходов, относительно клетки последнего хода.
    get_possible_moves( moves_history.at(moves_done - 1), possible_moves);

    // Смотрим, есть ли новый ход среди возможных.
    if(std::find(possible_moves.begin(), possible_moves.end(), GameCell(row, column)) != possible_moves.end()) {
        return true;
    }

    // Не нашли новый ход среди возможных.
    return false;
}

// Получить набор из 8 максимально возможных ходов, относительно переданной клетки поля.
void KnightsMove::get_possible_moves(const GameCell gcell, std::vector<GameCell> &gc_vect) const
{
    // Нужно преобразование к int для проверки на выход меньше 0.
    int base_row = static_cast<int>(gcell.row);
    int base_col = static_cast<int>(gcell.column);

    int tmp_row;
    int tmp_col;

    // Возможно максимум 8 ходов конём относительно заданной клетки.
    // Проверяем каждый и если возможен, запоминаем в переданном векторе.
    // Если ход не выходит за рамки поля, проверяем использована ли уже конечная клетка.

    // 1: +1 по номеру столбца и -2 по номеру строки
    tmp_col = base_col + 1;
    tmp_row = base_row - 2;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 2: +2 по номеру столбца и -1 по номеру строки
    tmp_col = base_col + 2;
    tmp_row = base_row - 1;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 3: +2 по номеру столбца и +1 по номеру строки
    tmp_col = base_col + 2;
    tmp_row = base_row + 1;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 4: +1 по номеру столбца и +2 по номеру строки
    tmp_col = base_col + 1;
    tmp_row = base_row + 2;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 5: -1 по номеру столбца и +2 по номеру строки
    tmp_col = base_col - 1;
    tmp_row = base_row + 2;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 6: -2 по номеру столбца и +1 по номеру строки
    tmp_col = base_col - 2;
    tmp_row = base_row + 1;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 7: -2 по номеру столбца и -1 по номеру строки
    tmp_col = base_col - 2;
    tmp_row = base_row - 1;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }

    // 8: -1 по номеру столбца и -2 по номеру строки
    tmp_col = base_col - 1;
    tmp_row = base_row - 2;

    if (check_bounds(tmp_row, tmp_col)) { // Пройдена проверка на выход за рамки игрового поля.
        if ( !cell_is_marked( static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col) )) {
            gc_vect.push_back( GameCell(static_cast<unsigned int>(tmp_row), static_cast<unsigned int>(tmp_col)));
        }
    }
}

// Проверить, лежат ли переданные координаты в рамках игрового поля.
bool KnightsMove::check_bounds(const int row, const int column) const
{
    if ((row < 0) || (column < 0)) return false;
    if (( static_cast<unsigned int>(row) >= side_size) || ( static_cast<unsigned int>(column) >= side_size)) return false;

    return true;
}

// Узнать, использована ли уже клекта по заданным координатам для хода.
bool KnightsMove::cell_is_marked(const unsigned int row, const unsigned int column) const
{
    size_t vector_position = static_cast<size_t>(row * side_size + column);
    if (vector_position >= array_size) {
        return false;
    }

    if ( moves_array.at(vector_position) == 0 ) { // Данная клетка поля свободна для хода.
        return false;
    }

    // Клетка уже использована.
    return true;
}

// Удалить заданное количество последних ходов. Переданное число не должно превышать кол-во уже сделанных.
bool KnightsMove::delete_moves(const size_t moves_number, std::vector<GameCell> &deleted_cells)
{
    if (moves_number > moves_done) {
        return false;
    }

    size_t vector_position;

    for(size_t i = 0; i < moves_number; ++i) {
        vector_position = static_cast<size_t>(moves_history.at(moves_done - 1 - i).row * side_size + moves_history.at(moves_done - 1 - i).column);
        moves_array[vector_position] = 0;
        deleted_cells.push_back(moves_history.at(moves_done - 1 - i));
    }

    if (moves_number == moves_done) {
        reject_game();
        return true;
    }

    if (!game_in_progress) game_in_progress = true;
    if (game_finished) game_finished = false;

    for(size_t i = 0; i < moves_number; ++i) {
        moves_history.pop_back();
    }

    moves_done -= moves_number;

    return true;
}
