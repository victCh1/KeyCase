#ifndef KEYSTABLEVIEW_H
#define KEYSTABLEVIEW_H

#include <QTableView>
#include <QItemDelegate>

class KeysTableView : public QTableView
{
public:

    KeysTableView(QWidget *parent = nullptr);
    void setModel(QAbstractItemModel *model) override;

    int initEditors();
    QLineEdit *editor(const QModelIndex &index) const;
    void setEditor(const QModelIndex &index, QLineEdit *editor);

protected slots:

    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    void rowsRemoved(const QModelIndex &parent, int first, int last);

private:

    QVector<QVector<QLineEdit*>> editors;

};

#endif // KEYSTABLEVIEW_H
