#ifndef PASSWORDDELEGATE_H
#define PASSWORDDELEGATE_H

#include <QItemDelegate>
#include <QStyledItemDelegate>

#include "keystableview.h"

class PasswordDelegate : public QItemDelegate
{
public:

    PasswordDelegate(QObject *parent = nullptr)
        : QItemDelegate(parent), tableView(static_cast<KeysTableView*>(parent)) {}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    KeysTableView *tableView;
};

class SimpleDelegate : public QItemDelegate
{
public:

    SimpleDelegate(QObject *parent = nullptr) : QItemDelegate(parent), tableView(static_cast<KeysTableView*>(parent)) {}

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    KeysTableView *tableView;
};

#endif // PASSWORDDELEGATE_H
