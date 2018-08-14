#ifndef KTASKWINDOW_H
#define KTASKWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "ktask.h"
#include <QLineEdit>

class QIntValidator;

namespace Ui {
class KTaskWindow;
}

class KTaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KTaskWindow(QVector<KTask> &container, QWidget *parent = 0);
    ~KTaskWindow();

    void fillTable(QVector<KTask> &container);

private slots:
    void on_pbAccept_clicked();

    void on_twTable_cellDoubleClicked(int row, int column);

    void on_pbCancel_clicked();

private:
    Ui::KTaskWindow *ui;
    QVector<KTask> & Tasks;
    QString sDone = "Done";
    QString sNotDone ="Not done";
    QIntValidator *intValidator = 0;

signals:
    void TaskWindowClosed();
};

#endif // KTASKWINDOW_H
