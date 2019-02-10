#include <QApplication>
#include <QtWidgets>
#include <iostream>

#include "Sender.h"

void main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "No argument.";
        return;
    }
    ImageSender sender("localhost", 4444);
    sender.SendImage(argv[1]);
}
