#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



class function
   {
public:
   int exit=0;
   int zaehler=0;
   int searchresult=0;

   char menuinput;
   char inputFile[100];
   char zeichen;
   char puffer[100];
   char searchinput[100];

   void menu();
   void loadxml();
   void loadtxt();
   void convert();
   void search();

   string usersearch;
   function();
   };

function::function(){}

enum zustandTyp {Start, inDaten};
enum zustandTyp zustand;

