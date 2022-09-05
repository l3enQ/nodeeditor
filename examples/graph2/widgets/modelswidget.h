#ifndef MODELSWIDGET_H
#define MODELSWIDGET_H

#include <QWidget>

class QStandardItemModel;
class QLineEdit;
class QTreeView;
class ModelsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModelsWidget(const QString &name, QStandardItemModel *model, QWidget *parent = nullptr);


signals:

private:
    QTreeView *_treeView;
    QLineEdit *_lineEditFilter;

    void setup(const QString &name);
    void setModel(QStandardItemModel *model = nullptr);
};

#endif // MODELSWIDGET_H
