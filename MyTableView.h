#pragma once

#include <QtWidgets>

class MyTableView : public QTableView
{
public:
    explicit MyTableView(QWidget *parent = nullptr)
    {
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->hide();

        QHeaderView *header = new QHeaderView(Qt::Horizontal);
        header->setFont(QFont((QFont("Times", 11, 100, 0))));
        header->setSortIndicatorShown(true);
        setHorizontalHeader(header);

        connect(horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, &MyTableView::onSortClick);

        setSortingEnabled(true);
    }
    void setModel(QAbstractItemModel *model)
    {
        QTableView::setModel(model);
        resizeColumnsToContents();
        m_sortedColumn = 0;
        m_sortOrder = Qt::SortOrder::AscendingOrder;
        sortByColumn(m_sortedColumn, m_sortOrder);
    }
public slots:
    void onSortClick(int colunm)
    {
        if(colunm == m_sortedColumn)
        {
            m_sortOrder = (m_sortOrder == Qt::SortOrder::AscendingOrder)?  Qt::SortOrder::DescendingOrder :  Qt::SortOrder::AscendingOrder;
        }
        else
        {
            m_sortedColumn = colunm;
            m_sortOrder = Qt::SortOrder::AscendingOrder;
        }
        sortByColumn(m_sortedColumn, m_sortOrder);
    }
private:
    Qt::SortOrder m_sortOrder = Qt::SortOrder::AscendingOrder;
    int m_sortedColumn = 0;
};
