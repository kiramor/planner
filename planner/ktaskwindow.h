#ifndef KTASKWINDOW_H
#define KTASKWINDOW_H

#include <QMainWindow>

namespace Ui {
class KTaskWindow;
}

class KTaskWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KTaskWindow(QWidget *parent = 0);
    ~KTaskWindow();

private:
    Ui::KTaskWindow *ui;
};

#endif // KTASKWINDOW_H
