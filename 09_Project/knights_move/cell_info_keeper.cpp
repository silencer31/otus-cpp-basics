#include "cell_info_keeper.h"

// Узнать статус ячейки по координатам.
CellStatus CellInfoKeeper::get_cell_status(const int row, const int column) const
{
    size_t vector_position = static_cast<size_t>(row * side_size + column);

    if (vector_position >= vector_size) {
        return CellStatus::Unused;
    }

    return cs_vector.at(vector_position);
}

// Установить статус ячейки.
void CellInfoKeeper::set_cell_status(const int row, const int column, const CellStatus cell_status)
{
    size_t vector_position = static_cast<size_t>(row * side_size + column);

    if (vector_position >= vector_size) {
        return;
    }

    cs_vector[vector_position] = cell_status;
}


// Сбросить состояние всех ячеек.
void CellInfoKeeper::reject_all_cells_status()
{
    for(size_t i = 0; i < vector_size; ++i) {
        cs_vector[i] = CellStatus::EmptyCell;
    }
}

// Удалить все подсказки следующего хода.
void CellInfoKeeper::reject_all_hints()
{
    for(size_t i = 0; i < vector_size; ++i) {
        if (cs_vector[i] == CellStatus::PossibleMove) {
            cs_vector[i] = CellStatus::EmptyCell;
        }
    }
}
