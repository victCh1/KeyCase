#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataloader.h"
#include "model.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static const QAction* getHidePasswordAction()   { return globalPasswordAct; }
    static const QColor& getSelectionColor()        { return selectionColor; }

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void addRecord();
    void editRecord();
    void removeRow();

private:
    inline void changeGlobalPasswordActState(bool hide);

    DataLoader* dataLoader = nullptr;
    KeyCaseModel* keyCaseModel = nullptr;
    Settings settings;
    QIcon hideIcon, showIcon;
    QAction* editAct, *removeAct;
    inline static QAction* globalPasswordAct;
    inline static QColor selectionColor { 220, 220, 220 };

    QVector<QString> headers { tr("Resource name/address"), tr("Login/key"), tr("Password") };

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
