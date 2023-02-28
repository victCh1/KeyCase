#ifndef KEYRECORD_H
#define KEYRECORD_H

#include <QDataStream>
#include <QString>

class KeyRecord
{
    friend QDataStream& operator << (QDataStream& out, const KeyRecord& record)
    {
        out << record.name << record.login << record.password;

        return out;
    }

    friend KeyRecord& operator >> (QDataStream& in, KeyRecord& record)
    {
        in >> record.name >> record.login >> record.password;

        return record;
    }

public:

    const QString& getName() const
    {
        return name;
    }

    const QString& getLogin() const
    {
        return login;
    }

    const QString& getPassword() const
    {
        return password;
    }

    void setName(const QString &newName)
    {
        name = newName;
    }

    void setLogin(const QString &newLogin)
    {
        login = newLogin;
    }

    void setPassword(const QString &newPassword)
    {
        password = newPassword;
    }

private:
    QString name;
    QString login;
    QString password;
};










#endif // KEYRECORD_H
