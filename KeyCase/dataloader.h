#ifndef DATALOADER_H
#define DATALOADER_H

#include <QByteArray>
#include <QString>

class DataLoader
{
public:
    DataLoader(const QString dirPath = "");
    virtual ~DataLoader() = default;

    virtual void loadData() = 0;
    virtual void saveData() = 0;

    const QByteArray &getData() const
    {
        return data;
    }    

    void setData(const QByteArray &newData)
    {
        data = newData;
    }

protected:
    QString filePath;
    QByteArray data;
};

class SimpleDataLoader : public DataLoader
{
public:
    ~SimpleDataLoader() = default;

    void loadData() override;
    void saveData() override;
};


#endif // DATALOADER_H
