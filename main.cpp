#include <QApplication>
#include <QtWidgets/QWidget>
#include <QStringListModel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QListView>
#include <QtWidgets/QTableView>
#include <QItemSelectionModel>
#include <QtWidgets/QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget wgt;

    QStringListModel model;
    model.setStringList(QStringList() << "Item1" << "Item2" << "Item3");

    QTreeView* pTreeView = new QTreeView;
    pTreeView-> setModel(&model);

    QListView* pListView = new QListView;
    pListView-> setModel(&model);

    QTableView* pTableView = new QTableView;
    pTableView-> setModel(&model);

    QItemSelectionModel selection(&model);
    pTreeView->setSelectionModel(&selection);
    pListView->setSelectionModel(&selection);
    pTableView->setSelectionModel(&selection);

    QHBoxLayout* pLayout = new QHBoxLayout;
    pLayout->addWidget(pTreeView);
    pLayout->addWidget(pListView);
    pLayout->addWidget(pTableView);
    wgt.setLayout(pLayout);

    wgt.show();

    return a.exec();
}
