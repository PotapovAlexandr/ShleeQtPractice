#include <QApplication>
#include <QtWidgets>
#include <ctime>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr));
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();


    return app.exec();
}
