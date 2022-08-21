#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QModelIndex>

#define ROW_HEIGHT 50
#define COLUMN_WIDTH 50

// Вывести на экран цифры и буквы для игрового поля.
void GameWindow::otput_digits_and_letters()
{
    QStandardItem *mod_item = nullptr;

    // Подготовка вертикальной линии с цифрами.
    vertical_table_model->insertColumn(0);
    vertical_table_model->insertRows( 0, side_size);

    ui->verticalDigitsView->horizontalHeader()->hide();
    ui->verticalDigitsView->verticalHeader()->hide();
    ui->verticalDigitsView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->verticalDigitsView->setModel(vertical_table_model);
    ui->verticalDigitsView->setShowGrid(true);
    ui->verticalDigitsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    unsigned int delta = side_size;
    for(unsigned int i = 0; i < side_size; ++i) {
        delta = side_size - i;
        vertical_table_model->setData(vertical_table_model->index(i, 0), QString::number(delta), Qt::DisplayRole);
        ui->verticalDigitsView->setRowHeight(i, ROW_HEIGHT);
        mod_item = vertical_table_model->item(i, 0);
        mod_item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    ui->verticalDigitsView->setColumnWidth(0, COLUMN_WIDTH);


    // Подготовка горизонтальной линии с буквами.
    horizontal_table_model->insertRow(0);
    horizontal_table_model->insertColumns(0, side_size);
    ui->horizontalLettersView->horizontalHeader()->hide();
    ui->horizontalLettersView->verticalHeader()->hide();
    ui->horizontalLettersView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->horizontalLettersView->setModel(horizontal_table_model);
    ui->horizontalLettersView->setShowGrid(true);
    ui->horizontalLettersView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->horizontalLettersView->setRowHeight(0, ROW_HEIGHT);
    for(unsigned int i = 0; i<side_size; ++i) {
        horizontal_table_model->setData(horizontal_table_model->index(0, i), QString('A'+i), Qt::DisplayRole);
        ui->horizontalLettersView->setColumnWidth(i, COLUMN_WIDTH);
        mod_item = horizontal_table_model->item(0, i);
        mod_item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

// Подготовка игрового поля для начала игры.
void GameWindow::prepare_game_field()
{
    user_moves_table_model->insertRows( 0, side_size);
    user_moves_table_model->insertColumns(0, side_size);

    ui->gameField->horizontalHeader()->hide();
    ui->gameField->verticalHeader()->hide();
    ui->gameField->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->gameField->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->gameField->setModel(user_moves_table_model);
    ui->gameField->setShowGrid(true);
    ui->gameField->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(unsigned int i = 0; i < side_size; ++i) {
        ui->gameField->setRowHeight(i, ROW_HEIGHT);
    }

    for(unsigned int i = 0; i < side_size; ++i) {
        ui->gameField->setColumnWidth(i, COLUMN_WIDTH);
    }
}

// Очищение игрового поля от всех ходов.
void GameWindow::clear_game_field()
{
    QModelIndex um_index;

    for(unsigned int i = 0; i < side_size; ++i) {
        for(unsigned int j = 0; j < side_size; ++j) {
            um_index = user_moves_table_model->index(i, j);
            user_moves_table_model->clearItemData(um_index);
        }
    }
}

// Очищение одной клетки поля.
void GameWindow::clear_one_cell( const unsigned int row, const unsigned int column )
{
    user_moves_table_model->clearItemData(user_moves_table_model->index(row, column));
}

// Отобразить на поле возможные ходы, относительно переданной ячейки.
void GameWindow::show_possible_moves(const unsigned int row, const unsigned int column)
{
    std::vector<GameCell> possible_moves;
    possible_moves.reserve(8);

    // Получаем набор возможных ходов, относительно клетки последнего хода.
    knights_move_ptr->get_possible_moves( GameCell(row, column), possible_moves);

    if ( possible_moves.empty()) {
        message_window_ptr->set_mode_show_message(QString("Больше нет доступных ходов!"));
        message_window_ptr->exec();
    }
    else {
        for(unsigned int i = 0; i < possible_moves.size(); ++i) {
            ci_keeper_ptr->set_cell_status( possible_moves.at(i).row, possible_moves.at(i).column, CellStatus::PossibleMove);
        }
    }
}

// Актуализация отображения ячеек на поле после отмены ходов.
void GameWindow::check_field_after_cancel()
{
    if (knights_move_ptr->game_is_in_progress()) { // Игра ещё продоллжается.
        // Подсвечиваем возможные ходы для поля, ставшего последним после удаления текущего.
        GameCell last_cell = knights_move_ptr->get_last_move_cell();
        show_possible_moves( last_cell.row, last_cell.column);
    }
    else {
        ui->pbCancelOneMove->setEnabled(false);
        ui->pbCancelMoves->setEnabled(false);

        message_window_ptr->set_mode_show_message(QString("Игра прекращена"));
        message_window_ptr->exec();
    }
}
