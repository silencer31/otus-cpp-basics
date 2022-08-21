#include "delegate/line_delegate.h"

#include <QPainter>

// Делегат для таблицы
void LineDelegate::paint(QPainter *pPainter,
           const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    //QStyle *style = option.widget->style();
    QStyleOptionViewItem option1 = option;
    this->initStyleOption(&option1, index);

#ifdef WIN32
    QFont font = QFont("Tahoma", 16, QFont::Normal);
#else
    QFont font = QFont("Open Sans", 16, QFont::Normal);
#endif

    option1.font = font;

    // Закрашивание прямоугольников таблицы.
    //QRect cbRect = option1.rect;


    QStyledItemDelegate::paint(pPainter, option1, index);
}

QSize LineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex& ) const
{
    return QSize( option.rect.width(), option.rect.height());
}
