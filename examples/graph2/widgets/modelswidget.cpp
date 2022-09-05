#include "modelswidget.h"

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QStandardItemModel>

#include "filtermodel.h"

ModelsWidget::ModelsWidget(const QString &name, QStandardItemModel *model, QWidget *parent)
    : QWidget{parent}
{
    setup(name);
    setModel(model);
}

void
ModelsWidget::
setModel(QStandardItemModel *model)
{
    auto proxy = new FilterModel(this);
    proxy->setSourceModel(model);
    _treeView->setModel(proxy);

    connect(_lineEditFilter, &QLineEdit::textEdited, this, [=](QString text) {
        proxy->setFilter(text);
    });
}

void
ModelsWidget::
setup(const QString &name)
{
    if (objectName().isEmpty())
        setObjectName(name);
    resize(300, 600);
    setMinimumSize(QSize(300, 300));

    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QToolButton *buttonDownload;
    QFrame *line;
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(4);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    verticalLayout->setContentsMargins(4, 4, 4, 4);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setMinimumSize(QSize(150, 0));
    label->setMaximumSize(QSize(200, 16777215));
    QFont font;
    font.setPointSize(11);
    font.setBold(true);
    label->setFont(font);
    label->setText(name);
    horizontalLayout->addWidget(label);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);

    buttonDownload = new QToolButton(this);
    buttonDownload->setObjectName(QString::fromUtf8("buttonDownload"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(buttonDownload->sizePolicy().hasHeightForWidth());
    buttonDownload->setSizePolicy(sizePolicy);
    buttonDownload->setMinimumSize(QSize(26, 26));
    buttonDownload->setMaximumSize(QSize(26, 26));
    buttonDownload->setFocusPolicy(Qt::NoFocus);
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/svg/download.svg"), QSize(), QIcon::Normal, QIcon::Off);
    buttonDownload->setIcon(icon1);
    buttonDownload->setIconSize(QSize(20, 20));
    buttonDownload->setAutoRaise(true);
    horizontalLayout->addWidget(buttonDownload);

    verticalLayout->addLayout(horizontalLayout);

    line = new QFrame(this);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    verticalLayout->addWidget(line);

    _lineEditFilter = new QLineEdit(this);
    _lineEditFilter->setObjectName(QString::fromUtf8("lineEditFilter"));
    _lineEditFilter->setMaximumSize(QSize(16777215, 16777215));
    _lineEditFilter->setDragEnabled(false);
    _lineEditFilter->setClearButtonEnabled(true);
    _lineEditFilter->setPlaceholderText("Search...");
    verticalLayout->addWidget(_lineEditFilter);

    _treeView = new QTreeView(this);
    _treeView->setObjectName(QString::fromUtf8("_treeView"));
    _treeView->setBaseSize(QSize(300, 0));
    _treeView->setIndentation(30);
    _treeView->setAnimated(true);
    _treeView->header()->setVisible(false);
    verticalLayout->addWidget(_treeView);

    verticalLayout->setStretch(3, 1);
}
