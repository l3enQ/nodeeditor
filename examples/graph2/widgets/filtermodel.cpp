#include "filtermodel.h"

FilterModel::
FilterModel(QObject *parent)
    : QSortFilterProxyModel(parent) {

}

bool
FilterModel::
filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (filter.isEmpty() || !source_parent.isValid())
        return true;

    return source_parent.model()->index(source_row, 0, source_parent).data().toString().contains(filter, Qt::CaseInsensitive);
}
