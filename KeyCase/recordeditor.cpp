
#include <QPushButton>
#include "recordeditor.h"
#include "ui_recordeditor.h"


RecordEditor::RecordEditor(KeyCaseModel* model, int row, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordEditor)
{
    ui->setupUi(this);    

    QDataWidgetMapper *mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->addMapping(ui->nameLineEdit, 0);
    mapper->addMapping(ui->loginLineEdit, 1);
    mapper->addMapping(ui->passwordLineEdit, 2);
    mapper->setCurrentIndex(row);
}

RecordEditor::~RecordEditor()
{
    delete ui;
    delete mapper;
}

void RecordEditor::setHeaders(const QVector<QString> &names)
{
    if(names.size() != 3)
        return;

    ui->nameLabel->setText(names[0]);
    ui->loginLabel->setText(names[1]);
    ui->passwordLabel->setText(names[2]);
    setMinimumHeight(height());
}

void RecordEditor::accept()
{
    if(ui->nameLineEdit->text().isEmpty() && ui->loginLineEdit->text().isEmpty() && ui->passwordLineEdit->text().isEmpty())
    {
        reject();
        return;
    }

    QDialog::accept();
}

