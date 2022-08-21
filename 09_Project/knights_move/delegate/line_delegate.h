#ifndef LINE_DELEGATE_H
#define LINE_DELEGATE_H

#pragma once

#include <QStyledItemDelegate>

// Делегат для таблицы
class LineDelegate : public QStyledItemDelegate
{
Q_OBJECT

public:
    explicit LineDelegate(QObject *pobj = 0) : QStyledItemDelegate(pobj) {}

    void paint(QPainter *pPainter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex& ) const;

private:

};

#endif // LINE_DELEGATE_H
