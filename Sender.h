#pragma once
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QImage>
#include <iostream>

class ImageSender: QObject
{
    Q_OBJECT
public:
    ImageSender(const QString& host, const int port):
        m_tcpSocket(new QTcpSocket(this))
      , m_host(host)
      , m_port(port)
    {}

    void SendImage(const QString& path)
    {
        if (CheckImage(path))
        {
            if (!ConnectToRecipient())
            {
                std::cout << "No connection" <<std::endl;
                return;
            }
            QFile file(path);
            file.open(QIODevice::ReadOnly);
            QByteArray data;
            data = file.readAll();

            m_tcpSocket->write(data);
            m_tcpSocket->waitForBytesWritten();
        }
        else
        {
            std::cout << "File name is not correct. Input image's filename." << std::endl;
        }
    }

public slots:
    void OnError(QAbstractSocket::SocketError err)
    {
        if( err == QAbstractSocket::HostNotFoundError)
        {
            std::cout << "Host was not found." << std::endl;
        }
        else if (err == QAbstractSocket::RemoteHostClosedError)
        {
            std::cout << "Host is closed." << std::endl;
        }
    }

private:
    bool CheckImage(const QString& path)
    {
        QFileInfo checked_file(path);
        return (checked_file.exists() && checked_file.isFile()/* && IsReadablePict(path)*/);
    }
//    Work only in debug.
//    bool IsReadablePict(const QString& path)
//    {
//        QImage testPict;
//        return testPict.load(path);
//    }

    bool ConnectToRecipient()
    {
        m_tcpSocket->connectToHost(m_host, m_port);
        connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnError(QAbstractSocket::SocketError)));
        return m_tcpSocket->waitForConnected();
    }

private:
    QTcpSocket *m_tcpSocket;
    QString m_host;
    int m_port;
};
