
#include <QHeaderView>
#include <QMessageBox>
#include <QPalette>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include "dataloader.h"
#include "recordeditor.h"
#include "passworddelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), hideIcon(":/hide.png"), showIcon(":/show.png")
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("Key Case"));
    setWindowIcon(QIcon(":/passwords_keys.png"));

    SimpleDataLoader dataLoader;

    keyCaseModel = new KeyCaseModel(new SimpleDataLoader(), this);
    keyCaseModel->setHeaders(headers);
    ui->keysTableView->setModel(keyCaseModel);

    ui->keysTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->keysTableView->horizontalHeader()->setFixedHeight(25);
    ui->keysTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->keysTableView->verticalHeader()->setDefaultSectionSize(24);
    ui->keysTableView->verticalHeader()->setFixedWidth(30);

    ui->keysTableView->verticalHeader()->hide();
    ui->keysTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->keysTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    SimpleDelegate *simpleDelegate = new SimpleDelegate(ui->keysTableView);
    ui->keysTableView->setItemDelegateForColumn(0, simpleDelegate);

    PasswordDelegate *passwordDelegate = new PasswordDelegate(ui->keysTableView);
    ui->keysTableView->setItemDelegateForColumn(1, passwordDelegate);
    ui->keysTableView->setItemDelegateForColumn(2, passwordDelegate);

    QAction *addAct = new QAction(QIcon(":/add.png"), tr("Add new record"), this);
    addAct->setShortcuts(QKeySequence::New);
    addAct->setStatusTip(tr("Add new record"));
    connect(addAct, &QAction::triggered, this, &MainWindow::addRecord);
    ui->toolBar->addAction(addAct);

    editAct = new QAction(QIcon(":/edit.png"), tr("Edit current record"), this);
    editAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_E));
    editAct->setStatusTip(tr("Edit current record"));
    connect(editAct, &QAction::triggered, this, &MainWindow::editRecord);
    ui->toolBar->addAction(editAct);

    removeAct = new QAction(QIcon(":/remove.png"), tr("Remove current record"), this);
    removeAct->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_R));
    removeAct->setStatusTip(tr("Remove current record"));
    connect(removeAct, &QAction::triggered, this, &MainWindow::removeRow);
    ui->toolBar->addAction(removeAct);

    QWidget* spacer = new QWidget();
    spacer->setMaximumSize(40, 40);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);

    ui->toolBar->addSeparator();

    globalPasswordAct = new QAction(this);
    globalPasswordAct->setCheckable(true);

    changeGlobalPasswordActState(settings.getHidePassword());
    globalPasswordAct->setChecked(!settings.getHidePassword());

    connect(globalPasswordAct, &QAction::triggered, this, [&](bool checked) {
        changeGlobalPasswordActState(!checked);
    });

    ui->toolBar->addAction(globalPasswordAct);

    restoreGeometry(settings.getWindowGeometry());

    QVector<int> columnWidth = settings.getColumnWidth();

    ui->keysTableView->setColumnWidth(0, columnWidth[0]);
    ui->keysTableView->setColumnWidth(1, columnWidth[1]);

    if(ui->keysTableView->initEditors())
        ui->keysTableView->selectRow(0);
    else {
        removeAct->setEnabled(false);
        editAct->setEnabled(false);
    }
}

inline
void MainWindow::changeGlobalPasswordActState(bool hide)
{
    if(hide) {
        globalPasswordAct->setIcon(hideIcon);
        globalPasswordAct->setToolTip(tr("Login/password are hidden"));
        globalPasswordAct->setStatusTip(tr("Login/password are hidden"));
    }
    else {
        globalPasswordAct->setIcon(showIcon);
        globalPasswordAct->setToolTip(tr("Login/password are open"));
        globalPasswordAct->setStatusTip(tr("Login/password are hidden"));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    settings.setWindowGeometry(saveGeometry());

    QVector<int> columnWidth{ ui->keysTableView->columnWidth(0), ui->keysTableView->columnWidth(1) };
    settings.setColumnWidth(columnWidth);

    settings.setHidePassword(!globalPasswordAct->isChecked());

    QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRecord()
{
    keyCaseModel->addRecord();
    RecordEditor* editor = new RecordEditor(keyCaseModel, 0, this);
    editor->setWindowTitle(tr("New record"));
    editor->setHeaders(headers);

    if(editor->exec() == QDialog::Rejected)
    {
        keyCaseModel->removeRows(0, 1);
    }
    else if(keyCaseModel->rowCount() == 1) {
        editAct->setEnabled(true);
        removeAct->setEnabled(true);
    }

    delete editor;
}

void MainWindow::editRecord()
{
    RecordEditor* editor = new RecordEditor(keyCaseModel, ui->keysTableView->currentIndex().row(), this);
    editor->setWindowTitle(tr("Editing the current record"));
    editor->setHeaders(headers);
    editor->exec();
    delete editor;
}

void MainWindow::removeRow()
{
    if(QMessageBox::question(this, tr("Deleting the current entry"), tr("Do you really want to delete the current entry?")) == QMessageBox::Yes) {

        keyCaseModel->removeRows(ui->keysTableView->currentIndex().row(), 1);
        if(!keyCaseModel->rowCount()) {
            editAct->setEnabled(false);
            removeAct->setEnabled(false);
        }
    }
}

