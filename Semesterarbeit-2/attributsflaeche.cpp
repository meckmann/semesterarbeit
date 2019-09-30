#include <QtGui>
#include "attributsflaeche.h"

Spielfigur position;
vector<Gegner> GegnerVector;

attributsFlaeche::attributsFlaeche(QWidget *parent)
    : QWidget(parent) {

    setFixedSize(660, 560);
    setPalette(QPalette(QColor(0, 0, 26)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    increment=0;
}

attributsFlaeche::~attributsFlaeche() {
}

void attributsFlaeche::paintEvent(QPaintEvent *) {

vector<Gegner>::iterator pos;
Gegner newGegner;

if(increment) {
    if(!input) {

        //Punkte
        points++;

        //Bewegung der Objekte/Gegner
        for (pos = GegnerVector.begin() ; pos != GegnerVector.end(); pos++) {
            pos->y = pos->y+50;
        }

        //Mach neue Objekte
    GegnerVector.push_back(newGegner);
    }
}
input = false;

QPainter lebensanzeige;
QPainter Spielfigur;
QPainter Punktestand;
QPainter Gegner;

//zeichnet die Healthbar
lebensanzeige.begin(this);
int lebensanzeigeX = 585;
for(int i = 0; i < 3; i++) {
    lebensanzeige.setBrush(QBrush(Qt::red));
    lebensanzeige.drawEllipse(lebensanzeigeX, 25, 25, 25);
    lebensanzeigeX = lebensanzeigeX+19;
}
lebensanzeige.end();

//zeichnet die Spielfigur
Spielfigur.begin(this);
Spielfigur.setBrush(QBrush(Qt::white, Qt::Dense2Pattern));
Spielfigur.drawRect(position.x, 500, 100, 40);
Spielfigur.end();

//zeichnet den Punktestand
Punktestand.begin(this);
Punktestand.setPen(QPen(Qt::yellow));
Punktestand.setFont(QFont("Helvetica", 25, QFont::Bold));
Punktestand.drawText(QPoint(15, 30), QString::number(points));
Punktestand.end();

//zeichnet gegnerische Figuren
Gegner.begin(this);
for (pos = GegnerVector.begin() ;pos != GegnerVector.end(); pos++) {
    Gegner.setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
    Gegner.drawRect(pos->x, pos->y, 15, 15);

//Löscht die gegnerischen Figuren
    if (pos->y > 659) {
    GegnerVector.erase(pos);
    }
}
Gegner.end();
}

//Steuerung
void attributsFlaeche::keyPressEvent( QKeyEvent *event ) {

switch ( event->key()) {
    case Qt::Key_Left:
        if(position.x - 15 >=0) {
            position.x = position.x - 15;
            input = true;
            update();
    }
    break;
    case Qt::Key_Right:
        if(position.x + 15 <= 590) {
            position.x = position.x + 15;
            input = true;
            update();
    }
    break;
    }
}

//Werte werden analysiert
void attributsFlaeche::serialize(QFile &file) {

   QTextStream out(&file);
   vector<Gegner>::iterator pos;

   out <<"P "<<  position.x<< " "<<  points  << endl;
   for (pos = GegnerVector.begin() ; pos != GegnerVector.end(); pos++) {
        out <<"O "<< pos->x << " " << pos->y << endl;
   }
}

//behandelt die Werte und erstellt neue Objekte
void attributsFlaeche::deserialize(QFile &file) {

   QTextStream in(&file);

   char v;

   GegnerVector.clear();

       while (in.status() == QTextStream::Ok) {
       in >> v;
       if (in.status() == QTextStream::ReadPastEnd)
       break;
       if(v == 'P') {
          position.x=0;
          in >> position.x>> points;
              }
       if(v=='O') {
        Gegner newGegner;
        in >> newGegner.x >> newGegner.y;
        GegnerVector.push_back(newGegner);
      }
update();
   }
}


