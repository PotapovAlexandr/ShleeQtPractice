#pragma once

#include <QtWidgets>
#include <QRandomGenerator>
#include "Worker.h"
#include <ctime>

namespace
{
    int s_million = 1000000;
    int s_fiftyMillions = s_million * 50;
}

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* pwgt = nullptr):
        QMainWindow(pwgt)
      , m_model(new QStringListModel(this))
      , m_threadCounter(0)
    {
        SetGui();
    }
    ~MainWindow(){}

    void MainWindow::closeEvent(QCloseEvent *event)
    {
        emit StopAll();
        QMainWindow::closeEvent(event);
    }

signals:
    void StopAll();

public slots:
    void OnAddTaskPush()
    {
        qDebug() << "worker started";
        QThread* thread = new QThread();

        int target = (std::rand()*std::rand())%s_fiftyMillions + s_million; // rand 1-50 kkk. 1-10kkk work so quickly.
        Worker* worker = new Worker(target);
        worker->moveToThread(thread);

        connect(this, &MainWindow::StopAll,
                worker, &Worker::StopWork, Qt::DirectConnection);

        connect(thread, &QThread::started,
                this, &MainWindow::IncrementThreadCounter);
        connect(thread, &QThread::started,
                worker, &Worker::StartWork);

        connect(worker, &Worker::ReturnResult,
                this, &MainWindow::OnResultReturned);
        connect(worker, &Worker::Finished,
                thread, &QThread::quit);

        connect(worker, &Worker::Finished,
                worker, &Worker::deleteLater);

        connect(thread, &QThread::finished,
                thread, &QThread::deleteLater);



        thread->start();

    }
    void OnResultReturned(int m_target, int count, int time)
    {
        {
            QMutexLocker lock(&m_modelMutex);
            QString str = QString::number(m_target) + ": " + QString::number(count) + " (" + QString::number(time/1000) + ")sec";
            if (count == 0)
            {
                str = "Interrupted by user";
            }
            m_model->setStringList(m_model->stringList()<<str);
        }
        {
            QMutexLocker lock(&m_counterMutex);
            --m_threadCounter;
            SetCounterLabelText();
        }
    }
    void IncrementThreadCounter()
    {
        QMutexLocker lock(&m_counterMutex);
        ++m_threadCounter;
        SetCounterLabelText();
    }

    void OnStopAllTask()
    {
        emit StopAll();
    }
private:
    void SetGui()
    {
        this->resize(300, 400);

        QWidget* wgt = new QWidget(this);

        QPushButton* button = new QPushButton("Add task", wgt);
        connect(button, &QPushButton::pressed, this, &MainWindow::OnAddTaskPush);

        QListView* listView = new QListView(wgt);
        listView->setModel(m_model);

        QHBoxLayout* layout = new QHBoxLayout(wgt);

        QVBoxLayout* rightLayout = new QVBoxLayout(wgt);
        rightLayout->setAlignment(Qt::AlignTop);

        m_lblThreadCounter = new QLabel(wgt);
        SetCounterLabelText();

        QPushButton* stopAllThreads = new QPushButton("Stop All Threads", wgt);
        connect(stopAllThreads, &QPushButton::pressed, this, &MainWindow::OnStopAllTask);

        rightLayout->addWidget(button);
        rightLayout->addWidget(m_lblThreadCounter);
        rightLayout->addWidget(stopAllThreads);

        layout->addWidget(listView);
        layout->addLayout(rightLayout);

        wgt->setLayout(layout);

        this->setCentralWidget(wgt);
    }
    void SetCounterLabelText()
    {
         m_lblThreadCounter->setText("Active Threads: " + QString::number(m_threadCounter));
    }

private:
    QStringListModel* m_model;
    QLabel* m_lblThreadCounter;
    int m_threadCounter;
    QMutex m_counterMutex;
    QMutex m_modelMutex;
};
