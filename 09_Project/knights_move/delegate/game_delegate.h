#ifndef GAME_DELEGATE_H
#define GAME_DELEGATE_H

#pragma once

#include <QStyledItemDelegate>

#include "cell_info_keeper.h"

// Делегат для таблицы с отображением ходов игрока.
class GameDelegate : public QStyledItemDelegate
{
Q_OBJECT

public:
    explicit GameDelegate(QObject *pobj = 0) : QStyledItemDelegate(pobj) {}

    ~GameDelegate() {
        ci_keeper_ptr = nullptr;
    }

    void paint(QPainter *pPainter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex& ) const;

    inline void set_cell_keeper_ptr(CellInfoKeeper *cik_ptr) {
        ci_keeper_ptr = cik_ptr;
    }

private:
    CellInfoKeeper *ci_keeper_ptr = nullptr;
};
#endif // GAME_DELEGATE_H
