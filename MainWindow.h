#pragma once

#include <QtWidgets>
#include <QTcpSocket>

#include "ui_m_form.h"
#include "Receiver.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* pwgt = nullptr):
        QMainWindow(pwgt)
      , rec(new Receiver(this))
      , m_image(nullptr)
    {
        SetGui();
        if (!rec->BindPort(4444))
        {
            m_ui.ImageLabel->setAlignment(Qt::AlignCenter);
            m_ui.ImageLabel->setText("Port is busy.");
        }
        connect(rec, SIGNAL(DownloadComplete(QString)), this, SLOT(onDownloadComplite(QString)));
    }
    ~MainWindow()
    {
        delete m_image;
    }



public slots:
    void onDownloadComplite(const QString& fileName)
    {
        m_image = new QPixmap();
        if(m_image->load(fileName))
        {
            int w = m_ui.ImageLabel->width();
            int h = m_ui.ImageLabel->height();
            m_ui.ImageLabel->setPixmap(m_image->scaled(w,h,Qt::KeepAspectRatio));
        }
        else
        {
            QMessageBox::critical(nullptr, "Error", "Downloaded file is not image.", QMessageBox::Ok);
            m_ui.ImageLabel->setAlignment(Qt::AlignCenter);
            m_ui.ImageLabel->setText("Downloaded file is not image.");
        }
    }
private:
    void SetGui()
    {
        m_ui.setupUi(this);
    }
    void MainWindow::resizeEvent(QResizeEvent* event)
    {
        QMainWindow::resizeEvent(event);
        if (!m_image)
        {
            return;
        }
        int w = m_ui.ImageLabel->width();
        int h = m_ui.ImageLabel->height();
        m_ui.ImageLabel->setPixmap(m_image->scaled(w,h,Qt::KeepAspectRatio));
    }

private:
    Ui_MainWindow m_ui;
    Receiver *rec;
    QPixmap* m_image;
};
