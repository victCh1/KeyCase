#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

public:

    Settings(QObject* parent = nullptr);
    ~Settings();

    const QVector<int> getColumnWidth()                     {   return columnWidth;                 }
    void setColumnWidth(const QVector<int> newVal)          {   columnWidth = newVal;               }

    const QByteArray& getWindowGeometry() const             {   return windowGeometry;              }
    void setWindowGeometry(const QByteArray &newGeometry)   {   windowGeometry = newGeometry;       }

    bool getHidePassword() const                            {   return hidePassword;                }
    void setHidePassword(bool newHidePassword)              {   hidePassword = newHidePassword;     }

private:

    void readSettingsFromFile();
    void writeSettingsFromFile();

    QVector<int> columnWidth;
    QByteArray windowGeometry;
    bool hidePassword;

    QSettings* settings;
};

#endif // SETTINGS_H
