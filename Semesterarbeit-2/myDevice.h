#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include "attributsflaeche.h"

class myDevice : public QWidget
{
    Q_OBJECT

public:
    myDevice(QWidget *parent = 0);

private:
    attributsFlaeche *meineattributsFlaeche;

private slots:
  void speichern();
  void laden();
  void start(void);
  void stop(void);


};
