#include "autoupdate.h"
#include <iostream>
#include <QDir>
using std::cout;
using std::endl;

AutoUpdater::AutoUpdater() {
    proc = new QProcess(this);

    timer = new QTimer(this);
    timer->setInterval(20000);
    timer->setSingleShot(false);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer, &QTimer::timeout, this, &AutoUpdater::doUpdate);

    timer->start();

    cout << "program started" << endl;
}

AutoUpdater::~AutoUpdater() {
    cout << "exiting..." << endl;

    timer->stop();

    if (proc->state() == QProcess::Running) {
        proc->terminate();
        cout << "waiting for the git process to terminate..." << endl;
        if (!proc->waitForFinished()) {
            cout << "error terminating the git process, killing..." << endl;
            proc->kill();
        }
    }
}

bool AutoUpdater::doUpdate() {
    cout << "updating...";

    QDir dir("index");
    if (!dir.exists())
        proc->start("git", QStringList() << "clone" << "https://gitcafe.com/Fsu0413/LuaSkillsForQSGSIndexTest" << "index");
    else
        proc->start("git", QStringList() << "-C" << "index" << "pull");

    if (!proc->waitForFinished(3600000)) {
        cout << endl << "update error, killing the git process..." << endl;
        proc->kill();
        return false;
    }

    cout << "done." << endl;
    return true;
}

