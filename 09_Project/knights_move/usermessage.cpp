#include "usermessage.h"
#include "ui_usermessage.h"

UserMessage::UserMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserMessage)
{
    ui->setupUi(this);

    // Убирает верхний хэдер окна.
    setWindowFlags(Qt::WindowTitleHint | Qt::ToolTip);

    // Не даёт переключиться на родительское окно, пока не закрыто это.
    this->setWindowModality(Qt::ApplicationModal);

    connect(ui->pbConfirm, SIGNAL(clicked(bool)), this, SLOT(accept()) );
    connect(ui->pbCancel, SIGNAL(clicked(bool)), this, SLOT(reject()) );
}

UserMessage::~UserMessage()
{
    delete ui;
}

// Настроить вид окна для показа вопроса пользователю.
void UserMessage::set_mode_ask_question(const QString &question)
{
    ui->pbConfirm->move( 20, 180);
    ui->pbConfirm->setText(QString("Да"));

    ui->pbCancel->setEnabled(true); // Показываем кнопку с отменой.
    ui->pbCancel->setVisible(true);

    ui->userMessage->setText(question);
    ui->userMessage->setAlignment(Qt::AlignCenter);
}

// Настроить вид окна для показа сообщения пользователю.
void UserMessage::set_mode_show_message(const QString &message)
{
    ui->pbConfirm->move( 120, 180);
    ui->pbConfirm->setText(QString("OK"));

    ui->pbCancel->setEnabled(false); // Прячем кнопку с отменой.
    ui->pbCancel->setVisible(false);

    if (message.contains("\n")) {
        ui->userMessage->clear();
        QStringList str_list = message.split("\n");
        foreach(QString str, str_list) {
            ui->userMessage->append(str);
            ui->userMessage->setAlignment(Qt::AlignCenter);
        }
    }
    else {
        ui->userMessage->setText(message);
        ui->userMessage->setAlignment(Qt::AlignCenter);
    }
}

