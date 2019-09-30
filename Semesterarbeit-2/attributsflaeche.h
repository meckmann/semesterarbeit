#include <QWidget>
#include <QTimer>
#include <QFile>
using namespace std;

//Spielfigur
class Spielfigur
{
public:
    int x=280;
};
//GEGNEROBJEKTE
class Gegner
{
public:
    int y = 0;
    int x = rand() % 620;
};

//Definiere die Klasse AttributsFläche
class attributsFlaeche : public QWidget
{
public:
    attributsFlaeche(QWidget *parent = 0);
    ~attributsFlaeche();
    void start(void) {timer->start(500); increment=1;}
    void stop(void) {timer->stop(); increment=0;}
    void serialize(QFile &file);
    void deserialize(QFile &file);
    void hit (QFile &file);
    bool input;

private:
    QTimer *timer;
    QColor color;
    int increment;
    int points = 0;

protected:
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
};
