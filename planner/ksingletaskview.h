#ifndef KSINGLETASKVIEW_H
#define KSINGLETASKVIEW_H

#include <QMainWindow>
#include <ktask.h>
#include <QListWidget>

namespace Ui {
class KSingleTaskView;
}

class KSingleTaskView : public QMainWindow
{
    Q_OBJECT

public:
    explicit KSingleTaskView(KTask& tsk, QWidget *parent = nullptr);
    ~KSingleTaskView();

private slots:
    void on_pbAccept_clicked();

private:
    KTask& Task;
    Ui::KSingleTaskView *ui;
    void fillWindow();

signals:
    void STaskViewClosed();
};

#endif // KSINGLETASKVIEW_H
