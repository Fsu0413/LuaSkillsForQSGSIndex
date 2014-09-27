#include "CodeDialog.h"
#include "ui_CodeDialog.h"
#include "syntaxhighlighter.h"

CodeDialog::CodeDialog(QFile &file, QWidget *parent) : QDialog(parent), ui(new Ui::CodeDialog) {
    ui->setupUi(this);

    QFontMetrics fm(ui->textEdit->font());
    ui->textEdit->setTabStopWidth(fm.width("    "));

    new LuaSyntaxHighlighter(ui->textEdit->document());

    file.open(QIODevice::ReadOnly);
    QString str = file.readAll();
    file.close();

    ui->textEdit->setText(str);
}

void CodeDialog::showEvent(QShowEvent *e) {
    e->accept();

    ui->textEdit->setFixedWidth(width());
    ui->textEdit->setFixedHeight(height());
}

void CodeDialog::resizeEvent(QResizeEvent *e) {
    e->accept();

    ui->textEdit->setFixedWidth(e->size().width());
    ui->textEdit->setFixedHeight(e->size().height());
}

CodeDialog::~CodeDialog() {
    delete ui;
}
