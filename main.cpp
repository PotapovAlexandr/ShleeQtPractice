#include <QApplication>
#include <QtWidgets>

#include "MainWindowColorSetter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget wgt;

    MainWindowColorSetter* comboBox = new MainWindowColorSetter(&wgt);

    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addWidget(comboBox);
    wgt.setLayout(pLayout);

    wgt.show();

    return a.exec();
}
