#ifndef __AUTOUPDATE_H__
#define __AUTOUPDATE_H__

#include <QTimer>
#include <QProcess>

class AutoUpdater : public QObject {
    Q_OBJECT

public:
    AutoUpdater();
    ~AutoUpdater();

private slots:
    bool doUpdate();

private:
    QProcess *proc;
    QTimer *timer;
};

#endif
