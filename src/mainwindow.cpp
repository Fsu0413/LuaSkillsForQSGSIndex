#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "garbage.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setFixedSize(800, 580);

    const Garbage &garbage = *Garbage::getInstance();
    
    foreach (const General *general, garbage.getGenerals())
        ui->lstClass->addItem(general->objectName());
    
    connect(ui->lstClass, &QListWidget::currentItemChanged, this, &MainWindow::skillUpdate);
}

void MainWindow::skillUpdate(QListWidgetItem *currentItem, QListWidgetItem *) {
    QString current = currentItem->text();

    const Garbage &garbage = *Garbage::getInstance();
    const General *general = garbage.getGeneral(current);
    if (general != NULL) {
        while (ui->lstSkill->count() != 0)
            delete ui->lstSkill->takeItem(0);

        foreach (QString skill, general->getSkills())
            ui->lstSkill->addItem(skill);
    }

}

MainWindow::~MainWindow() {
    delete ui;
}
