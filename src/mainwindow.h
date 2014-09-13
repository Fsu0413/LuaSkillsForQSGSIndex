#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>
#include "garbage.h"
#include <QListWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void skillUpdate(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // MAINWINDOW_H
