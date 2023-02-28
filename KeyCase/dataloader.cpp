
#include "dataloader.h"
#include <QFile>
#include <QApplication>

DataLoader::DataLoader(const QString dirPath)
{
    if(QFile::exists(dirPath))
        filePath = dirPath + "/.casedata";
    else
        filePath = QApplication::applicationDirPath() + "/.casedata";
}
//-----------------------------------------------------------------
void SimpleDataLoader::loadData()
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly))
        return;

    data = file.readAll();

    file.close();
}
//-----------------------------------------------------------------
void SimpleDataLoader::saveData()
{
    QFile file(filePath);

    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(data);
}
//-----------------------------------------------------------------
