#ifndef KTASKWINDOW_H
#define KTASKWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "ktask.h"

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

private:
    Ui::KTaskWindow *ui;
    QVector<KTask> & Tasks;
};

#endif // KTASKWINDOW_H
