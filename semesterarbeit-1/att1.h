class ClattToken
   {

public:
   int getAttList(char *eingabe);
   char *zeigeAttName(int id) {return attName[id];}
   char *zeigeAttWert(int id) {return attValue[id];}
   int zahlAtt() {return anzahlAtt;}

private:
   int anzahlAtt;
   char *attName[5];
   char *attValue[5];

};
