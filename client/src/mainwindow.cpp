#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "garbage.h"
#include "CodeDialog.h"
#include "skill_translator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setFixedSize(800, 580);

    const Garbage &garbage = *Garbage::getInstance();
    
    foreach (const General *general, garbage.getGenerals()) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData(Qt::UserRole + 1, general->objectName());
        item->setText(SkillTranslator::translate(general->objectName()));
        ui->lstClass->addItem(item);
    }
    
    connect(ui->lstClass, &QListWidget::currentItemChanged, this, &MainWindow::skillUpdate);
    connect(ui->btnDisplayCode, &QPushButton::clicked, this, &MainWindow::showSkill);
}

void MainWindow::skillUpdate(QListWidgetItem *currentItem, QListWidgetItem *) {
    QString current = currentItem->data(Qt::UserRole + 1).toString();

    const Garbage &garbage = *Garbage::getInstance();
    const General *general = garbage.getGeneral(current);
    if (general != NULL) {
        while (ui->lstSkill->count() != 0)
            delete ui->lstSkill->takeItem(0);

        foreach (QString skill, general->getSkills()) {
            QListWidgetItem *item = new QListWidgetItem;
            item->setData(Qt::UserRole + 1, skill);
            item->setText(SkillTranslator::translate(skill));
            ui->lstSkill->addItem(item);
        }
    }

}

void MainWindow::showSkill(bool) {
    QListWidgetItem *currentItem = ui->lstSkill->currentItem();
    if (currentItem != NULL) {
        QString currentSkill = currentItem->data(Qt::UserRole + 1).toString();
        QString currentGeneral = ui->lstClass->currentItem()->data(Qt::UserRole + 1).toString();

        const Garbage &garbage = *Garbage::getInstance();
        const General *general = garbage.getGeneral(currentGeneral);
        if (general != NULL) {
            QString skill_owner = general->getSkillOwner(currentSkill);
            if (skill_owner != currentGeneral)
                general = garbage.getGeneral(skill_owner);

            if (general != NULL) {
                QString package = general->getPackage();
                QString file_name = "skills/" + package + "/" + skill_owner + "_" + currentSkill + ".lua";
                QFile file(file_name);
                if (file.exists())
                    (new CodeDialog(file, this))->show();
                else
                    QMessageBox::critical(this, tr("Error"), QString(tr("Cannot read file %1")).arg(file_name));

                return;
            }
        }
        QMessageBox::critical(this, tr("Error"), tr("Unknown Error"));
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
