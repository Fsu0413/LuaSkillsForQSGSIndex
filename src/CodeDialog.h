#ifndef __CODEDIALOG_H__
#define __CODEDIALOG_H__

#include <QDialog>
#include <QFile>

namespace Ui {
    class CodeDialog;
}

class CodeDialog : public QDialog {
    Q_OBJECT

public:
    explicit CodeDialog(QFile &file, QWidget *parent = NULL);
    ~CodeDialog();

protected:
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *);

private:
    Ui::CodeDialog *ui;
};

#endif