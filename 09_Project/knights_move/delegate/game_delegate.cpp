#include "delegate/game_delegate.h"
#include "extra_functions.h"

#include <QPainter>

void GameDelegate::paint(QPainter *pPainter,
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

    // Закрашивание клеток игрового поля.
    QRect cbRect = option1.rect;
    QColor bgCBColor;

    CellStatus cell_status = CellStatus::Unused;

    if ( ci_keeper_ptr != nullptr) {
        cell_status = ci_keeper_ptr->get_cell_status(index.row(), index.column());
    }

    switch (cell_status) {
    case CellStatus::Unused:
        bgCBColor = qRgba(255, 255, 255, 255);
        break;
    case CellStatus::EmptyCell:
        if ( is_even(index.row()) && is_even(index.column())) {
            bgCBColor = qRgba(225, 225, 225, 255);
        } else if ( !is_even(index.row()) && !is_even(index.column()) ) {
            bgCBColor = qRgba(225, 225, 225, 255);
        }
        else {
            bgCBColor = qRgba(198, 198, 198, 255);
        }

        break;
    case CellStatus::PossibleMove:
        bgCBColor = qRgba(170, 255, 127, 255);
        break;
    case CellStatus::CheckedCell:
        bgCBColor = qRgba(170, 170, 127, 255);
        break;
    default:
        bgCBColor = qRgba(255, 255, 255, 255);
        break;
    }

    pPainter->fillRect(cbRect, QBrush(bgCBColor));

    QStyledItemDelegate::paint(pPainter, option1, index);
}

QSize GameDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex& ) const
{
    return QSize( option.rect.width(), option.rect.height());
}
