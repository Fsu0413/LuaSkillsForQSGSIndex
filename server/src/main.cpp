#include <QCoreApplication>
#include "autoupdate.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    AutoUpdater au;
    (void)au;

    return a.exec();
}
