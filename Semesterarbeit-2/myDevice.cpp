#include <QtGui>
#include "myDevice.h"

myDevice::myDevice(QWidget *parent)
    : QWidget(parent)
{   //Knöpfe für Laden, Speichern, Start und Stop

    QPushButton *laden = new QPushButton(tr("Laden"));
    laden->setFont(QFont("Helvetica", 16, QFont::Normal));
    connect(laden, SIGNAL(clicked()), this, SLOT(laden()));

    QPushButton *speichern = new QPushButton(tr("Speichern"));
    speichern->setFont(QFont("Decorative", 16, QFont::Normal));
    connect(speichern, SIGNAL(clicked()), this, SLOT(speichern()));

    QPushButton *start = new QPushButton(tr("Start"));
    start->setFont(QFont("TypeWriter", 16, QFont::Normal));
    connect(start, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *stop = new QPushButton(tr("Stop"));
    stop->setFont(QFont("OldEnglish", 16, QFont::Normal));
    connect(stop, SIGNAL(clicked()), this, SLOT(stop()));




    meineattributsFlaeche = new attributsFlaeche;
    //Layout wird erstellt
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(laden, 1, 3);
    gridLayout->addWidget(speichern, 2, 3);

    gridLayout->addWidget(start, 4, 3);
    gridLayout->addWidget(stop, 5, 3);


    gridLayout->addWidget(meineattributsFlaeche, 0, 2, 0, 1);
    gridLayout->setColumnStretch(12, 1);
    setLayout(gridLayout);
}

//laden
void myDevice::laden() {
    QFileDialog dialog(this);
        QString fileName;
        QFile file;

        dialog.setFileMode(QFileDialog::AnyFile);
        fileName = dialog.getOpenFileName(this,
                                          tr("Laden mit"), ".", tr("(*.myz)"));

        if (fileName.isNull()==false)
        {
            file.setFileName(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::warning(this, tr("Error 404"),
                                     tr("Das folgende File ist nicht korrekt:") + fileName,QMessageBox::Ok);
            }

            meineattributsFlaeche->deserialize(file);
            file.close();
            return;
        }
}

//speichern
void myDevice::speichern() {
    QFileDialog dialog(this);
        QString fileName;
        QFile file;

        dialog.setFileMode(QFileDialog::AnyFile);
        fileName = dialog.getSaveFileName(this,
                                          tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));
        if (fileName.isNull()==false)
        {
            file.setFileName(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this, tr("Dateifehler"),
                                     tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
            }
            meineattributsFlaeche->serialize(file);
            file.close();
            return;
        }
}


//start
void myDevice::start(void)
{
    meineattributsFlaeche->start();
    meineattributsFlaeche->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}
//stop
void myDevice::stop(void)
{
    meineattributsFlaeche->stop();
}
