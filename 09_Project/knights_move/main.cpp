#include "gamewindow.h"
#include "usermessage.h"
#include "cell_info_keeper.h"
#include "knights_move.h"
#include "extra_functions.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#define GAME10X10 10
#define GAME8X8 8
#define GAME5X5 5

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // Приложение.

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "knights_move_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    unsigned int default_size = GAME10X10;
    unsigned int side_size = 0; // Кол-во клеток стороны игрового поляю

    // Читаем входной параметр, если такой был.
    if (argc > 1) {
        side_size = read_user_size(argc, argv);

        if (side_size == 0) {
            return -1;
        }
    }
    else {
        side_size = default_size; // Пользователь не стал передавать свой размер.
    }

    // Проверка, что не превышает максимальный размер.
    if (side_size > GAME10X10) {
        std::cout << "Unsupported game field size: " << side_size << std::endl;
        return -1;
    }

    GameWindow game_window(side_size); // Главное окно программы.
    UserMessage message_window; // Окно для показа сообщений или вопроса пользователю.
    CellInfoKeeper ci_keeper(side_size); // Класс - хранитель состояния клеток игрового поля.
    KnightsMove knights_move(side_size);  // Класс, реализующий логику игры и контролирующий её прогресс.

    game_window.set_message_window_ptr( &message_window);
    game_window.set_ci_keeper_ptr( &ci_keeper);
    game_window.set_knights_move_ptr( &knights_move);

    game_window.show();

    return a.exec(); // Запуск цикла обработки событий приложения.
}
