
#include <QGuiApplication>
#include "passwordlineedit.h"
#include "mainwindow.h"

PasswordLineEdit::PasswordLineEdit(QWidget* parent, bool current)
    : QLineEdit(parent), darkCopyIcon(QIcon(":/copy_dark.png")), lightCopyIcon(QIcon(":/copy_light.png")),
                         hideIcon(QIcon(":/hide.png")), showIcon(":/show.png")
{
    clipboard = QGuiApplication::clipboard();

    setReadOnly(true);
    setFrame(false);
    setTextMargins(1, 0, 0, 1);
    setContextMenuPolicy(Qt::NoContextMenu);

    globalPasswordAct = MainWindow::getHidePasswordAction();

    localPasswordAct = new QAction(this);
    changeLocalPasswordActState(!globalPasswordAct->isChecked());

    connect(localPasswordAct, &QAction::triggered, this, [&]() {
        changeLocalPasswordActState(echoMode() == QLineEdit::Normal);
    });

    addAction(localPasswordAct, QLineEdit::TrailingPosition);

    copyAct = new QAction(this);
    copyAct->setCheckable(true);
    clipboardCleared(false);

    addAction(copyAct, QLineEdit::TrailingPosition);
    connect(copyAct, &QAction::triggered, this, [&](bool checked) {

                if(checked) {
                    clipboard->setText(text());
                    textCopied();
                }
                else {
                    if(clipboard->text() == text())
                        clipboard->clear();

                    clipboardCleared();
                }
    });

    connect(this, &PasswordLineEdit::textChanged, this, &PasswordLineEdit::clipboardDataChanged);

    connect(globalPasswordAct, &QAction::triggered, this, [&](bool checked) {
                changeLocalPasswordActState(!checked);
    });

    setCurrent(current);
}

inline
void PasswordLineEdit::changeLocalPasswordActState(bool hide)
{
    if(hide) {
        localPasswordAct->setIcon(hideIcon);
        localPasswordAct->setToolTip(tr("Login/password are hidden"));
        localPasswordAct->setStatusTip(tr("Login/password are hidden"));
        setEchoMode(QLineEdit::Password);
    }
    else {
        localPasswordAct->setIcon(showIcon);
        localPasswordAct->setToolTip(tr("Login/password are open"));
        localPasswordAct->setStatusTip(tr("Login/password are open"));
        setEchoMode(QLineEdit::Normal);
    }
}

void PasswordLineEdit::setCurrent(bool current)
{
    if(current) {
        //setStyleSheet("QLineEdit { selection-color: black; selection-background-color: " + selectionColor.name() + "; "
        //                                                            "background-color: " + selectionColor.name() + ";/* font: bold;*/ }");"

        setStyleSheet("QLineEdit { selection-color: black; selection-background-color: " + MainWindow::getSelectionColor().name() + "; "
                                                                    "background-color: " + MainWindow::getSelectionColor().name() + ";/* font: bold;*/ }");
        copyAct->setVisible(true);
        localPasswordAct->setVisible(true);
    }
    else {
        setStyleSheet("");
        copyAct->setVisible(false);
        localPasswordAct->setVisible(false);
    }
}

inline void PasswordLineEdit::textCopied()
{
    connect(clipboard, &QClipboard::dataChanged, this, &PasswordLineEdit::clipboardDataChanged);

    copyAct->setIcon(darkCopyIcon);
    copyAct->setToolTip(tr("Clear clipboard"));
    copyAct->setStatusTip(tr("Clear clipboard"));

}

inline void PasswordLineEdit::clipboardCleared(bool connected)
{
    if(connected)
        disconnect(clipboard, &QClipboard::dataChanged, this, &PasswordLineEdit::clipboardDataChanged);

    copyAct->setIcon(lightCopyIcon);
    copyAct->setToolTip(tr("Copy to clipboard"));
    copyAct->setStatusTip(tr("Copy to clipboard"));
}

// slot
void PasswordLineEdit::clipboardDataChanged()
{
    if(clipboard->text() != text()) {
        this->actions()[1]->setIcon(lightCopyIcon);
        if(copyAct->isChecked())
            copyAct->setChecked(false);
    }
}

void PasswordLineEdit::setText(const QString &text)
{
    if(clipboard->text() == text)
    {
        copyAct->setChecked(true);
        textCopied();
    }

    QLineEdit::setText(text);
}

//-------------------------------------------
SimpleLineEdit::SimpleLineEdit(QWidget* parent, bool current)
    : QLineEdit(parent)
{
    setReadOnly(true);
    setFrame(false);
    setTextMargins(1, 0, 0, 1);
    setContextMenuPolicy(Qt::NoContextMenu);

    setCurrent(current);
}

void SimpleLineEdit::setCurrent(bool current)
{
    if(current) {
        //setStyleSheet("QLineEdit { selection-color: black; selection-background-color: " + selectionColor.name() + "; "
        //                                                            "background-color: " + selectionColor.name() + "; /*font: bold;*/ }");
        setStyleSheet("QLineEdit { selection-color: black; selection-background-color: " + MainWindow::getSelectionColor().name() + "; "
                                                                    "background-color: " + MainWindow::getSelectionColor().name() + "; /*font: bold;*/ }");
    }
    else {
        setStyleSheet("");
    }
}
