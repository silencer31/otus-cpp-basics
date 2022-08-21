#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QRegExpValidator>

GameWindow::GameWindow(unsigned int side_cells_number, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , side_size(side_cells_number)
{
    ui->setupUi(this);

    // Соединяем кнопки на экране и методы отбработки их нажатий.
    // Нажатие по элементу представления.
    connect(ui->gameField, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(game_cell_clicked(const QModelIndex &)));
    connect(ui->pbStartGame, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(ui->pbCancelOneMove, SIGNAL(clicked()), this, SLOT(cancel_one_move()));
    connect(ui->pbCancelMoves, SIGNAL(clicked()), this, SLOT(cancel_moves()));
    connect(ui->pbExit, SIGNAL(clicked()), this, SLOT(exit_game()));

    // Динамическое создание моделей данных.
    user_moves_table_model = new QStandardItemModel();
    if (user_moves_table_model == nullptr) this->close();

    vertical_table_model = new QStandardItemModel();
    if (vertical_table_model == nullptr) this->close();

    horizontal_table_model = new QStandardItemModel();
    if (horizontal_table_model == nullptr) this->close();

    // Динамическое создание делегатов и соединение их с моделями данных.
    user_moves_delegate = new GameDelegate(user_moves_table_model); // Создание делегата.
    if (user_moves_delegate == nullptr) this->close();
    ui->gameField->setItemDelegate( user_moves_delegate ); // Устанавливаем делегат в представление.

    digits_delegate = new LineDelegate(vertical_table_model); // Создание делегата.
    if (digits_delegate == nullptr) this->close();
    ui->verticalDigitsView->setItemDelegate( digits_delegate ); // Устанавливаем делегат в представление.

    letters_delegate = new LineDelegate(horizontal_table_model); // Создание делегата.
    if (letters_delegate == nullptr) this->close();
    ui->horizontalLettersView->setItemDelegate( letters_delegate ); // Устанавливаем делегат в представление.

    // Блокируем кнопки отмены хода пока не начнется игра.
    ui->pbCancelOneMove->setEnabled(false);
    ui->pbCancelMoves->setEnabled(false);

    // Установка фильтра ввода для поля с отменой нескольких ходов.
    QRegExp rg("[0-9][0-9][0-9][0-9][0-9]");
    QRegExpValidator *cmValidator = new QRegExpValidator(rg, 0);
    ui->leMovesNumber->setValidator(cmValidator);

    // Вывод на экран цифр и букв вокруг игрового поля.
    otput_digits_and_letters();

    // Подготовка игрового поля для начала игры.
    prepare_game_field();
}

GameWindow::~GameWindow()
{
    if (letters_delegate != nullptr) {
        delete letters_delegate;
    }

    if (digits_delegate != nullptr) {
        delete digits_delegate;
    }

    if (user_moves_delegate != nullptr) {
        delete user_moves_delegate;
    }

    if (horizontal_table_model != nullptr) {
        delete horizontal_table_model;
    }

    if (vertical_table_model != nullptr) {
        delete vertical_table_model;
    }

    if (user_moves_table_model != nullptr) {
        delete user_moves_table_model;
    }

    message_window_ptr = nullptr; // Указатель на окно для сообщений или вопросов пользователю.
    ci_keeper_ptr = nullptr; // Указатель на хранитель состояний клеток игрового поля.
    knights_move_ptr = nullptr; // Указатель на объект с логикой игры.

    delete ui;
}

// Обработка клика по ячейке игрового поля.
void GameWindow::game_cell_clicked(const QModelIndex &cell_index)
{
     if ( !knights_move_ptr->game_is_in_progress()) {
         return;
     }

    if (!cell_index.isValid()) {
        return;
    }

    if (knights_move_ptr->make_move( static_cast<unsigned int>(cell_index.row()), static_cast<unsigned int>(cell_index.column()))) {
        user_moves_table_model->setData(cell_index, QString::number(knights_move_ptr->get_moves_done()), Qt::DisplayRole);
        QStandardItem *mod_item = user_moves_table_model->item(cell_index.row(), cell_index.column());
        mod_item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ci_keeper_ptr->reject_all_hints(); // Удалить все подсказки, которые были для этого хода.
        ci_keeper_ptr->set_cell_status( static_cast<unsigned int>(cell_index.row()), static_cast<unsigned int>(cell_index.column()), CellStatus::CheckedCell);

        if (knights_move_ptr->game_is_finished()) {
            message_window_ptr->set_mode_show_message(QString("Поздравляем!\nИгра окончена"));
            message_window_ptr->exec();
        }
        else { // Проверяем наличие следующих возможных ходов.
            show_possible_moves( static_cast<unsigned int>(cell_index.row()), static_cast<unsigned int>(cell_index.column()) );
        }

        ui->gameField->repaint();
    }
    else {
        message_window_ptr->set_mode_show_message(QString("На данную клетку ход невозможен"));
        message_window_ptr->exec();
    }
}

// Начало игры.
void GameWindow::start_game()
{
    if (knights_move_ptr->game_is_in_progress()) { // Игра уже идёт.
        message_window_ptr->set_mode_ask_question(QString("Желаете начать игру с начала?"));
        if ( message_window_ptr -> exec() == QDialog::Accepted ) {
            knights_move_ptr->reject_game();
            ci_keeper_ptr->reject_all_cells_status();
            clear_game_field(); // Очистка модели данных с ходами.

            knights_move_ptr->start_game();

            ui->gameField->repaint();
        }
    }
    else {
        if (knights_move_ptr->game_is_finished()) {
            knights_move_ptr->reject_game();
            ci_keeper_ptr->reject_all_cells_status();
            clear_game_field(); // Очистка модели данных с ходами.
        }

        knights_move_ptr->start_game();

        message_window_ptr->set_mode_show_message(QString("Можно начать с любой клетки"));
        message_window_ptr->exec();

        // Разблокируем кнопки отмены хода.
        ui->pbCancelOneMove->setEnabled(true);
        ui->pbCancelMoves->setEnabled(true);
    }

}

// Отмена одного последнего хода.
void GameWindow::cancel_one_move()
{
    if (knights_move_ptr->get_moves_done() == 0) {
        message_window_ptr->set_mode_show_message(QString("Чтобы отменить нужно сделать хотя бы один ход"));
        message_window_ptr->exec();
        return;
    }

    std::vector<GameCell> deleted_moves;
    deleted_moves.reserve(1);

    // Удаляем последний ход из объекта-игры.
    if (!knights_move_ptr->delete_moves(1, deleted_moves)) {
        return;
    }

    ci_keeper_ptr->reject_all_hints(); // Убираем все текущие подсказки.

    // Удаляем последний ход с игрового поля.
    clear_one_cell( deleted_moves.at(0).row, deleted_moves.at(0).column );

    // Убираем подсветку ячейки.
    ci_keeper_ptr->set_cell_status( deleted_moves.at(0).row, deleted_moves.at(0).column, CellStatus::EmptyCell);

    check_field_after_cancel(); // Актуализация вида игрового поля.

    ui->gameField->repaint();
}

// Отмена нескольких ходов.
void GameWindow::cancel_moves()
{
    if (knights_move_ptr->get_moves_done() == 0) {
        message_window_ptr->set_mode_show_message(QString("Чтобы отменить нужно сделать хотя бы один ход"));
        message_window_ptr->exec();
        return;
    }

    // Читаем кол-во ходов на удаление.
    QString mn_str = ui->leMovesNumber->text();
    ui->leMovesNumber->clear();

    bool ok = false;
    int moves_number = mn_str.toInt(&ok);
    if (!ok) {
        message_window_ptr->set_mode_show_message(QString("Необходимо указать корректное количество ходов"));
        message_window_ptr->exec();
        return;
    }

    std::vector<GameCell> deleted_moves;
    deleted_moves.reserve(moves_number);

    // Удаляем последний ход из объекта-игры.
    if (!knights_move_ptr->delete_moves(static_cast<size_t>(moves_number), deleted_moves)) {
        message_window_ptr->set_mode_show_message(QString("Ошибка отмены указанного количества ходов"));
        message_window_ptr->exec();
        return;
    }

    ci_keeper_ptr->reject_all_hints(); // Убираем все текущие подсказки.

    // Удаляем с игрового поля отменённые ходы и их подсветку.
    for(unsigned int i = 0; i < deleted_moves.size(); ++i) {
        clear_one_cell( deleted_moves.at(i).row, deleted_moves.at(i).column );
        ci_keeper_ptr->set_cell_status( deleted_moves.at(i).row, deleted_moves.at(i).column, CellStatus::EmptyCell);
    }

    check_field_after_cancel(); // Актуализация вида игрового поля.

    ui->gameField->repaint();
}

// Отмена нескольких ходов.
void GameWindow::exit_game()
{
    if (knights_move_ptr->game_is_in_progress()) { // Игра уже идёт.
        message_window_ptr->set_mode_ask_question(QString("Уверены, что хотите прервать игру?"));
        if ( message_window_ptr -> exec() == QDialog::Accepted ) {
            this->close();
        }
    }
    else {
        this->close();
    }
}
