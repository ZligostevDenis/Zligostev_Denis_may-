#include <QApplication>
#include "autorisation.h"
#include "mainwindow.h"
#include "autorisation.h"

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(editabletreemodel);

    QApplication app(argc, argv);
    MainWindow window;
    Autorisation autwindow;
    autwindow.show();

    return app.exec();
}
