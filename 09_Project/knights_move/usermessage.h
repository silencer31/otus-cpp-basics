#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <QDialog>

namespace Ui {
class UserMessage;
}

class UserMessage : public QDialog
{
    Q_OBJECT

public:
    explicit UserMessage(QWidget *parent = nullptr);
    ~UserMessage();

    void set_mode_ask_question(const QString &question); // Настроить вид окна для показа вопроса пользователю.
    void set_mode_show_message(const QString &message);  // Настроить вид окна для показа сообщения пользователю.

private:
    Ui::UserMessage *ui;
};

#endif // USERMESSAGE_H
