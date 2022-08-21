#ifndef CELL_INFO_KEEPER_H
#define CELL_INFO_KEEPER_H

#pragma once

#include <vector>

// Виды состояний клеток игрового поля.
enum class CellStatus{
    EmptyCell, //Пустая клетка игрового поля.
    PossibleMove, // Тоже пустая клетка, но на неё можно сделать ход.
    CheckedCell, // На эту клетку уже сделан ход.
    Unused // Клетка не используется в игре.
};

// Класс хранит состояние каждой клетки игрового поля.
class CellInfoKeeper{
public:
    explicit CellInfoKeeper(const unsigned int new_side_size ) : side_size(new_side_size) {
        vector_size = side_size * side_size;

        cs_vector.reserve(vector_size);

        for(size_t i = 0; i < vector_size; ++i) {
            cs_vector.push_back(CellStatus::EmptyCell);
        }
    }

    // Нам не нужны копии объекта данного класса.
    CellInfoKeeper(const CellInfoKeeper& cik) = delete;
    CellInfoKeeper& operator=(const CellInfoKeeper& cik) = delete;

    ~CellInfoKeeper() {
        cs_vector.clear();
    }

    // Узнать статус ячейки по координатам.
    CellStatus get_cell_status(const int row, const int column) const;

    // Установить статус ячейки.
    void set_cell_status(const int row, const int column, const CellStatus cell_status);

    // Сбросить состояние всех ячеек.
    void reject_all_cells_status();

    // Удалить все подсказки следующего хода.
    void reject_all_hints();

private:
    std::vector<CellStatus> cs_vector; // Массив с состояниями всех клеток игрового поля.
    size_t vector_size; // Размер массива.

    unsigned int side_size; // Размер одной стороны игрового поля.
};

#endif // CELL_INFO_KEEPER_H
