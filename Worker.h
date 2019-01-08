#pragma once

#include <QtWidgets>


class Worker: public QObject
{
    Q_OBJECT
public:
    Worker(int target):m_target(target), isAborted(false)
    {}
    ~Worker(){}

public slots:
    void StartWork()
    {
        int count = 0;
        QTime start = QTime::currentTime();
        count = CountSimpleNumbers();
        int time = start.elapsed();
        emit ReturnResult(m_target, count, time);
        emit Finished();
    }

    void StopWork()
    {
        isAborted = true;
    }

signals:
    void ReturnResult(int m_target, int count, int time);
    void Finished();

private:
    int CountSimpleNumbers()
    {
        int count = 0;
        QBitArray simpleNumbers(m_target + 1, true);

        for (int p = 2; p < m_target + 1; ++p)
        {
            if (simpleNumbers[p])
            {
                ++count;
                for (unsigned long int j = p*p; j < m_target + 1; j += p)
                {
                    if (isAborted)
                    {
                        return 0;
                    }
                    simpleNumbers.setBit(j, false);
                }
            }
        }
        return count;
    }
private:
    int m_target;
    bool isAborted;
};
