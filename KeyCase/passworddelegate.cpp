
#include <QPainter>
#include <QStylePainter>
#include <QLabel>
#include "passworddelegate.h"
#include "passwordlineedit.h"

QWidget* PasswordDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option) Q_UNUSED(index)

    PasswordLineEdit* passwordLineEdit = static_cast<PasswordLineEdit*>(tableView->editor(index));
    if(!passwordLineEdit) {
        passwordLineEdit = new PasswordLineEdit(parent, tableView->currentIndex() == index);
        tableView->setEditor(index, passwordLineEdit);
    }

    return passwordLineEdit;
}

void PasswordDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<PasswordLineEdit*>(editor)->setText(index.data().toString());
}

void PasswordDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor, option, index);
}

//--------------------------------------------------------
QWidget* SimpleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option) Q_UNUSED(index)

    SimpleLineEdit* simpleLineEdit = static_cast<SimpleLineEdit*>(tableView->editor(index));
    if(!simpleLineEdit) {
        simpleLineEdit = new SimpleLineEdit(parent, tableView->currentIndex() == index);
        tableView->setEditor(index, simpleLineEdit);
    }

    return simpleLineEdit;
}

void SimpleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<QLineEdit*>(editor)->setText(index.data().toString());
}

void SimpleDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor, option, index);
}




