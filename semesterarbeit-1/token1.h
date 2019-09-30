#include "att1.h"

class ClToken
   {
private:
    char *tokenStart;
    char *tokenEnde;
    char *tokenInhalt;
public:
   ClToken();
   char const *start() { if (tokenStart != NULL) return tokenStart; else return ""; }
   char const *end() { if (tokenEnde != NULL) return tokenEnde; else return ""; }
   char const *inhalt() { if (tokenInhalt != NULL) return tokenInhalt; else return ""; }
   int getToken(ifstream &datei);
   ClattToken att;

   } ;

enum zustand { istStartTag, istEndTag } ;
