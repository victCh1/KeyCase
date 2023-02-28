
#include <QApplication>
#include <QFile>
#include "settings.h"

Settings::Settings(QObject* parent)
    : QObject(parent)
{
    QString settingsPath = QApplication::applicationDirPath() + "/KeyCase.ini";

    settings = new QSettings(settingsPath, QSettings::IniFormat, this);
    readSettingsFromFile();
}

Settings::~Settings()
{
    writeSettingsFromFile();
}

void Settings::readSettingsFromFile()
{
    windowGeometry = settings->value("geometry").toByteArray();

    QStringList widthList = settings->value("column_width", QStringList{"300", "300"}).toStringList();
    for(auto &w : widthList)
        columnWidth << w.toInt();

    hidePassword = settings->value("hide_password", true).toBool();
}

void Settings::writeSettingsFromFile()
{
    settings->setValue("geometry", windowGeometry);

    QStringList widthList;
    for(auto i : columnWidth)
        widthList << QString::number(i);
    settings->setValue("column_width", widthList);

    settings->setValue("hide_password", hidePassword);
}

