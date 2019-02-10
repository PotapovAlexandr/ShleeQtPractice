#pragma once
#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QTemporaryFile>
#include <iostream>

#include "Utils.h"

namespace
{
    const QString s_fileName = "tempFile";

    void ShowError(const QString& error)
    {
        QMessageBox::critical(nullptr, "Error", error, QMessageBox::Ok);
    }
}

class Receiver: public QTcpServer
{
    Q_OBJECT
public:
    Receiver(QObject *parent = nullptr):
        QTcpServer(parent)
      , m_file(new QFile(s_fileName, this))
    {}

    bool BindPort(const int port)
    {
        if (!listen(QHostAddress::Any, port))
        {
            ShowError(errorString());
            close();
            return false;
        }
        connect(this, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
        return true;
    }
signals:
    void DownloadComplete(const QString& fileName);

public slots:
    void OnNewConnection()
    {
        m_file->open(QIODevice::WriteOnly);
        QTcpSocket* socket = nextPendingConnection();
        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
        connect(socket, SIGNAL(readyRead()), this, SLOT(OnReadyRead()));
        connect(socket, SIGNAL(readChannelFinished()), this, SLOT(OnReadComplete()));
    }

    void OnReadyRead()
    {
        QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
        if(!socket)
        {
            ShowError("Socket Error.");
            return;
        }

        QByteArray data;
        do
        {
            data = socket->readAll();
            m_file->write(data.constData(), data.size());
        }while(data.size());

    }
    void OnReadComplete()
    {
        m_file->close();
        DownloadComplete(s_fileName);
    }
private:
    QFile* m_file;
};
