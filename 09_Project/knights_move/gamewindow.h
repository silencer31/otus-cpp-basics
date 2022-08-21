#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#pragma once

#include <QMainWindow>
#include <QStandardItemModel>

#include "usermessage.h"
#include "cell_info_keeper.h"
#include "knights_move.h"
#include "delegate/game_delegate.h"
#include "delegate/line_delegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(unsigned int side_cells_number, QWidget *parent = nullptr);
    ~GameWindow();

    inline void set_message_window_ptr(UserMessage *um_ptr) { message_window_ptr = um_ptr; }

    void set_ci_keeper_ptr(CellInfoKeeper *cik_ptr) {
        ci_keeper_ptr = cik_ptr;

        if (user_moves_delegate != nullptr) {
            user_moves_delegate->set_cell_keeper_ptr(ci_keeper_ptr);
        }
    }

    inline void set_knights_move_ptr(KnightsMove *km_ptr) { knights_move_ptr = km_ptr; }

private slots: // Методы - реакции на сигналы.
    void game_cell_clicked(const QModelIndex &cell_index); // Обработка клика по ячейке игрового поля.
    void start_game(); // Начать игру.
    void cancel_one_move(); // Отмена одного хода.
    void cancel_moves(); // Отмена нескольких ходов.
    void exit_game(); // Выход из игры.

private: // Методы для внутреннего использования.
    void otput_digits_and_letters(); // Вывести на экран цифры и буквы для игрового поля.
    void prepare_game_field(); // Подготовка игрового поля для начала игры.
    void clear_game_field(); // Очищение игрового поля от всех ходов.
    void clear_one_cell(const unsigned int row, const unsigned int column); // Очищение одной клетки поля.
    void show_possible_moves(const unsigned int row, const unsigned int column); // Отобразить на поле возможные ходы, относительно переданной ячейки.
    void check_field_after_cancel(); // Актуализация отображения ячеек на поле после отмены ходов.

private: // Внутренние данные.
    Ui::GameWindow *ui;

    unsigned int side_size; // Размер одной стороны игрового поля.

    UserMessage *message_window_ptr = nullptr; // Указатель на окно для сообщений или вопросов пользователю.
    CellInfoKeeper *ci_keeper_ptr = nullptr; // Указатель на хранитель состояний клеток игрового поля.
    KnightsMove *knights_move_ptr = nullptr; // Указатель на объект с логикой игры.

    // Указатели для моделей данных .
    QStandardItemModel *user_moves_table_model = nullptr; // Для отображения ходов игрока.
    QStandardItemModel *vertical_table_model = nullptr;   // Для отображения цифр по вертикали.
    QStandardItemModel *horizontal_table_model = nullptr; // Для отображения букв по горизонтали.

    // Делегаты для моделей и таблиц
    GameDelegate *user_moves_delegate = nullptr; // Делегат для таблицы с ходами игрока.
    LineDelegate *digits_delegate = nullptr;  // Делегат для таблицы с цифрами.
    LineDelegate *letters_delegate = nullptr; // Делегат для таблицы с буквами.
};
#endif // GAMEWINDOW_H
