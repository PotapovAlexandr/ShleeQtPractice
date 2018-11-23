#pragma once

#include <QtWidgets>


class MainWindowColorSetter: public QComboBox
{
public:
    explicit MainWindowColorSetter(QWidget *parent = nullptr): QComboBox(parent), m_wgt(parent), m_settings("settings.ini", QSettings::IniFormat)
    {

        m_wgt->setFixedSize(400, 200);
        m_wgt->setWindowTitle("Test Application");

        setFixedSize(200, 50);
        addItems({"Red", "Yellow", "Green"});

        setItemData(0, QColor(Qt::red),    Qt::BackgroundRole);
        setItemData(1, QColor(Qt::yellow), Qt::BackgroundRole);
        setItemData(2, QColor(Qt::green),  Qt::BackgroundRole);

        ReadSettings();

        //connect(this, QComboBox::currentIndexChanged, this, &MainWindowColorSetter::OnItemChoosed); // этот вариант не сработал. поставил костыль.
        connect(this, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, static_cast<void (MainWindowColorSetter::*)(int)>(&MainWindowColorSetter::OnItemChoosed));
    }
    ~MainWindowColorSetter()
    {
        WriteSettings();
    }

public slots:
    void OnItemChoosed(int item)
    {
        switch (item) {
        case 0:
            m_wgt->setStyleSheet("QWidget { background-color: red; font-size : 15pt; }");
            break;
        case 1:
            m_wgt->setStyleSheet("QWidget { background-color: yellow; font-size : 15pt; }");
            break;
        case 2:
            m_wgt->setStyleSheet("QWidget { background-color: green; font-size : 15pt; }");
            break;
        default:
            break;
        }
    }
private:
    void ReadSettings()
    {
        int choosedItem = m_settings.value("/Settings/item", "0").toInt();
        setCurrentIndex(choosedItem);
        OnItemChoosed(choosedItem);
    }
    void WriteSettings()
    {
        m_settings.setValue("Settings/item", currentIndex());
        m_settings.sync();
    }


private:
    QWidget* m_wgt; // можно обернуть, но этот объект разрушится после разрушения родителя, а значит потерь не должно быть.
    QSettings m_settings;
};
