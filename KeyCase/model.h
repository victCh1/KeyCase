#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "dataloader.h"
#include "keyrecord.h"


class KeyCaseModel : public QAbstractTableModel
{
public:
    KeyCaseModel(DataLoader *dataLoader, QObject *parent = nullptr);
    ~KeyCaseModel();

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void setHeaders(const QVector<QString> &newHeaders);

public slots:
    void addRecord();
    //void removeRecord(int row);

private:
    //

    void loadRecords(DataLoader *loader);
    void saveRecords(DataLoader *loader);

    QVector<QString> headers;
    int columns = 0;
    QVector<KeyRecord> records;
    DataLoader *loader;
};



#endif // MODEL_H
