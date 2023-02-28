
#include <QLineEdit>
#include "keystableview.h"
#include "model.h"
#include "passwordlineedit.h"

KeysTableView::KeysTableView(QWidget *parent)
    : QTableView(parent)
{
}

int KeysTableView::initEditors()
{
    editors.resize(model()->rowCount());

    for(int i {0}; i < model()->rowCount(); ++i) {
        editors[i].resize(3);
        editors[i][0] = new SimpleLineEdit(viewport(), i == 0);
        editors[i][1] = new PasswordLineEdit(viewport(), i == 0);
        editors[i][2] = new PasswordLineEdit(viewport(), i == 0);

        openPersistentEditor(model()->index(i, 0));
        openPersistentEditor(model()->index(i, 1));
        openPersistentEditor(model()->index(i, 2));
    }

    return model()->rowCount();
}

QLineEdit* KeysTableView::editor(const QModelIndex &index) const
{
    if(index.row() < editors.count()) {
        return editors[index.row()][index.column()];
    }

    return nullptr;
}

void KeysTableView::setEditor(const QModelIndex &index, QLineEdit* editor)
{
    if(index.row() < editors.count()) {
        editors[index.row()][index.column()] = editor;
    }
}

void KeysTableView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(previous.isValid() && current.isValid() && current.row() != previous.row()) {

        if(previous.row() < editors.count()) {
            static_cast<SimpleLineEdit*>(editors[previous.row()][0])->setCurrent(false);
            static_cast<PasswordLineEdit*>(editors[previous.row()][1])->setCurrent(false);
            static_cast<PasswordLineEdit*>(editors[previous.row()][2])->setCurrent(false);
        }
    }

    if(current.isValid()) {

        if(current.row() < editors.count()) {
            static_cast<SimpleLineEdit*>(editors[current.row()][0])->setCurrent(true);
            static_cast<PasswordLineEdit*>(editors[current.row()][1])->setCurrent(true);
            static_cast<PasswordLineEdit*>(editors[current.row()][2])->setCurrent(true);
        }
    }

    QTableView::currentChanged(current, previous);
}

void KeysTableView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    editors.insert(0, { nullptr, nullptr, nullptr });
    openPersistentEditor(model()->index(0, 0));
    openPersistentEditor(model()->index(0, 1));
    openPersistentEditor(model()->index(0, 2));

    QTableView::rowsInserted(parent, start, end);
}

void KeysTableView::setModel(QAbstractItemModel *model)
{
    connect(model, &KeyCaseModel::rowsRemoved, this, &KeysTableView::rowsRemoved);

    QTableView::setModel(model);
}

void KeysTableView::rowsRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)

    editors.remove(first, last - first + 1);
}





