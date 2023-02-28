#ifndef RECORDEDITOR_H
#define RECORDEDITOR_H

#include <QDialog>
#include <QDataWidgetMapper>
#include "model.h"

namespace Ui {
class RecordEditor;
}

class RecordEditor : public QDialog
{
    Q_OBJECT

public:
    /*explicit */RecordEditor(KeyCaseModel* model, int row = 0, QWidget *parent = nullptr);
    ~RecordEditor();

    void setHeaders(const QVector<QString> &names);

private:
    Ui::RecordEditor *ui;
    QDataWidgetMapper *mapper {nullptr};
    void accept() override;
};

#endif // RECORDEDITOR_H
