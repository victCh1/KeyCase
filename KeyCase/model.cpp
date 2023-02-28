
#include <QDebug>
#include <QBuffer>
#include <QBuffer>
#include <QColor>

#include "model.h"
#include "keyrecord.h"

KeyCaseModel::KeyCaseModel(DataLoader *dataLoader, QObject *parent)
    : QAbstractTableModel(parent), loader(dataLoader)
{
    loadRecords(loader);
}

KeyCaseModel::~KeyCaseModel()
{
    saveRecords(loader);
    delete loader;
}

void KeyCaseModel::loadRecords(DataLoader *loader)
{
    loader->loadData();

    QByteArray dataArray = loader->getData();
    QBuffer dataBuf(&dataArray);
    dataBuf.open(QIODevice::ReadOnly);

    QDataStream in(&dataBuf);

    while(!in.atEnd())
    {
        KeyRecord record;
        in >> record;
        records.push_back(record);
    }
}

void KeyCaseModel::saveRecords(DataLoader *loader)
{
    QByteArray dataArray;
    QBuffer dataBuf(&dataArray);

    dataBuf.open(QIODevice::WriteOnly);

    QDataStream out(&dataBuf);

    for(auto record : records)
    {
        out << record;
    }

    dataBuf.close();
    loader->setData(dataArray);
    loader->saveData();
}

void KeyCaseModel::setHeaders(const QVector<QString> &newHeaders)
{
    headers = newHeaders;
}

QVariant KeyCaseModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::TextAlignmentRole)
    {
        if(orientation == Qt::Horizontal)
            return int(Qt::AlignLeft | Qt::AlignVCenter);
        else if(orientation == Qt::Vertical)
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Vertical)
            return ++section;
        else if(orientation == Qt::Horizontal)
        {
            return headers[section];
        }
    }

    return QVariant();
}

int KeyCaseModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {

        return 0;
    }

    return records.count();
}

int KeyCaseModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return headers.count();
}

QVariant KeyCaseModel::data(const QModelIndex &index, int role) const
{
    if(!checkIndex(index))
            return QVariant();

    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        int row = index.row();
        int column = index.column();

        switch(column)
        {
            case 0:
                return records[row].getName();
            case 1:
                return records[row].getLogin();
            case 2:
                return records[row].getPassword();
            default:
                break;
        }
    }

    return QVariant();
}

bool KeyCaseModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!checkIndex(index))
        return false;

    if(role == Qt::EditRole)
    {
        int row = index.row();
        int column = index.column();

        switch(column)
        {
            case 0:
                records[row].setName(value.toString());
                break;
            case 1:
                records[row].setLogin(value.toString());
                break;
            case 2:
                records[row].setPassword(value.toString());
                break;
            default:
                break;
        }
    }


    //emit dataChanged(index, index, QList<int>(role));
    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags KeyCaseModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

bool KeyCaseModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row >= records.count())
        return false;

    beginRemoveRows(parent, row, row + count - 1);

    records.removeAt(row);

    endRemoveRows();

    return true;
}

// Добавление строки сверху
void KeyCaseModel::addRecord()
{
    beginInsertRows(QModelIndex(), 0, 0);

    records.prepend(KeyRecord());                                                                  // вставляем новые строки сверху

    endInsertRows();
}

