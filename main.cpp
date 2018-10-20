#include <QApplication>
#include <QtWidgets>

#include "MyTableView.h"

void FillData(std::vector<QString>& tableElements)
{
    tableElements.push_back("Майерс");
    tableElements.push_back("Эффективное использование STL");
    tableElements.push_back("2001");

    tableElements.push_back("Шлии");
    tableElements.push_back("Qt 5.3");
    tableElements.push_back("2015");

    tableElements.push_back("Бентли");
    tableElements.push_back("Жемчужины программирования");
    tableElements.push_back("2002");

    tableElements.push_back("Сапковский");
    tableElements.push_back("Ведьмак");
    tableElements.push_back("1998");

    tableElements.push_back("Достоевский");
    tableElements.push_back("Великое пятикнижие");
    tableElements.push_back("1870");
}

void FillModel(const std::vector<QString>& tableElements, QStandardItemModel& model)
{
    for(int row = 0; row < model.rowCount(); ++row)
    {
        for(int column = 0; column < model.columnCount(); ++column)
        {
            model.setItem(row, column, new QStandardItem(tableElements.at(row*3 + column)));

        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    std::vector<QString> tableElements;
    FillData(tableElements);

    QWidget wgt;
    wgt.setGeometry(500, 300, 500, 500);

    QStandardItemModel model(tableElements.size()/3, 3);
    model.setHeaderData(0, Qt::Horizontal, QObject::tr("Автор"));
    model.setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    model.setHeaderData(2, Qt::Horizontal, QObject::tr("Год"));
    FillModel(tableElements, model);

    MyTableView* pTableView = new MyTableView();
    pTableView->setModel(&model);

    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addWidget(pTableView);
    wgt.setLayout(pLayout);

    wgt.show();

    return a.exec();
}
