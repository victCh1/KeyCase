#ifndef PASSWORDLINEEDIT_H
#define PASSWORDLINEEDIT_H

#include <QLineEdit>
#include <QClipboard>

class PasswordLineEdit : public QLineEdit
{
    Q_OBJECT

public:

    PasswordLineEdit(QWidget* parent, bool current = false);
    void setText(const QString &);
    void setCurrent(bool current);

private slots:
    void clipboardDataChanged();

private:
    inline void textCopied();
    inline void clipboardCleared(bool connected = true);
    inline void changeLocalPasswordActState(bool hide);

    QClipboard *clipboard {nullptr};
    QAction *localPasswordAct {nullptr};
    const QAction* globalPasswordAct {nullptr};
    QAction *copyAct {nullptr};
    QIcon darkCopyIcon, lightCopyIcon, hideIcon, showIcon;
};

class SimpleLineEdit : public QLineEdit
{
    Q_OBJECT

public:

    SimpleLineEdit(QWidget* parent, bool current = false);
    void setCurrent(bool current);
};

#endif // PASSWORDLINEEDIT_H
