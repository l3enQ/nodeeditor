#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModel: public QSortFilterProxyModel
{
public:
    explicit FilterModel(QObject *parent = nullptr);
    ~FilterModel(){}

    void setFilter(QString text) {
        filter = text;
        invalidate();
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

    QString filter;
};

#endif // FILTERMODEL_H
