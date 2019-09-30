#include "function.h"
#include <fstream>
#include <token1.h>
#include <string.h>
#include <kardashians.h>
#include <string>
#include <vector>

using namespace std;

ifstream eingabe;
ofstream ausgabe;
vector<kardashians>kardashiansVector;

void function::menu()
{
    cout<<"Hello! Welcome! \nTo load your files please press ENTER."<<endl;
    cin.get();
    cout<<"\nLoad your XML-File: ";
    cin>>this->inputFile;
    this->loadxml();
    cout<<"File is loaded."<<endl;
    cout<<"\nLoad TXT-File: ";
    cin>>this->inputFile;
    this->loadtxt();
    cout<<"File is loaded."<<endl;

    for(;exit==0;)
    {
        cout<<"--------------"<<endl;
        cout<<"---(C)onvert--"<<endl;
        cout<<"---(E)xit-----"<<endl;
        cout<<"---(S)earch---"<<endl;
        cout<<"--------------"<<endl;
        cout<<"-------C/E/S: "<<endl;
        cin>>menuinput;

        switch(menuinput)
        {
        case 'C': {
        convert();
        break;}
        case 'c': {
        convert();
        break;}

        case 'S': {
        search();
        break;}
        case 's': {
        search();
        break;}

        case 'E':{
        exit=1;
        break;}
        case 'e':{
        exit=1;
        break;}

        default:
        cout<<"unknown command."<<endl;;
        break;
        }
      }
}
void function::loadxml()
{
    eingabe.open(this->inputFile);
    ClToken token;

    string name;
    string instafollower;
    string photos;
    string id;
    string type;

    zaehler=0;

    for (;;)
    {
        if (token.getToken(eingabe)==0) break;
        for (int i=0;i<token.att.zahlAtt();i++)
        {
           if(strcmp(token.att.zeigeAttName(i),"id")==0)
               {
                id=token.att.zeigeAttWert(i);
               }
        }

        if(strcmp(token.end(),"name")==0)
        {
           name=token.inhalt();
        }
        else if(strcmp(token.end(),"type")==0)
        {
           type=token.inhalt();
        }
        else if(strcmp(token.end(),"instafollower")==0)
        {
           instafollower=token.inhalt();
        }
        else if(strcmp(token.end(),"photos")==0)
        {
           photos=token.inhalt();
        }
        else if(strcmp(token.end(),"product")==0)
        {   kardashians productObject;

            productObject.id=id;
            productObject.name=name;
            productObject.instafollower=instafollower;
            productObject.photos=photos;
            productObject.type=type;

            kardashiansVector.push_back(productObject);
        }
    }
    eingabe.close();
}
void function::loadtxt()
{
    eingabe.open(this->inputFile);

    string id;
    string shelf;
    string row;

    zaehler=0;
    zustand=Start;

    for (zaehler=0;;)
            {
            eingabe.get(zeichen);
            if (eingabe.eof())
            {
                puffer[zaehler]='\0';
                row=puffer;

                for (vector<kardashians>::iterator it=kardashiansVector.begin();it!=kardashiansVector.end();it++)
                {
                    string storage=it->id;
                   if(strcmp(storage.c_str(),id.c_str())==0)
                   {
                   it->stockinfo.push_back(shelf);
                   it->stockinfo.push_back(row);
                   }
                }
                break;
            }

            switch(zeichen)
               {
                case ' ':
                   if (zaehler)
                      {
                       puffer[zaehler]='\0';
                       zaehler=0;
                  if(zustand==Start)
                       {
                        id=puffer;}
                       else
                       {
                       shelf=puffer;
                       }
                      zustand=inDaten;
                    }
                   break;
                case '\n':
                    if (zaehler)
                       {
                       puffer[zaehler]='\0';
                       row=puffer;
                       zaehler=0;

                       for (vector<kardashians>::iterator it=kardashiansVector.begin();it!=kardashiansVector.end();it++)
                       {
                          string storage=it->id;
                          if(strcmp(storage.c_str(),id.c_str())==0)
                          {
                            it->stockinfo.push_back(shelf);
                            it->stockinfo.push_back(row);
                          }
                       }
                       zustand=Start;
                    }
                   break;
                default:
                   puffer[zaehler]=zeichen;
                   zaehler++;
                   break;
                   }
                }
        eingabe.close();
    }
void function::convert()
{
    cout<<"XML-File destination: "<<endl;
    cin>>inputFile;

    ausgabe.open(inputFile);
    ausgabe<< "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"<<endl;
    ausgabe << "<listKardashians>\n";
    for (vector<kardashians>::iterator it=kardashiansVector.begin();it!=kardashiansVector.end();it++)
    {
        ausgabe<<"<product>\n<details>\n<name id=\""<<it->id<<"\">"<<it->name<<"</name>\n<type>"<<it->type<<"</type>\n";
        ausgabe<<"<instafollower>"<<it->instafollower<<"</instafollower>\n<photos>"<<it->photos<<"</photos>\n</details>\n<stock>\n";
        for(int unsigned index=0;index<it->stockinfo.size();index++){
        ausgabe<<"<shelf>"<<it->stockinfo[index]<<"</shelf>\n<row>"<<it->stockinfo[index+1]<<"</row>\n";index++;
}

        ausgabe << "</stock>\n</product>\n";
    }
    ausgabe << "</listKardashians>\n";

    cout << "File created.\n" <<endl;
    ausgabe.close();
}
void function::search()
{
    cout<<"Search for name, type,photos or instafollower: "<<endl;
    cin>>usersearch;
    cout<<"\nSearch in "<<usersearch<<" for: "<<endl;
    cin.ignore();
    cin.getline(searchinput,100);

    for(int unsigned index=(0);index<kardashiansVector.size();index++)
    {
        if((strcmp(kardashiansVector[index].name.c_str(),searchinput)==0&&strcmp(usersearch.c_str(),"name")==0)||
           (strcmp(kardashiansVector[index].type.c_str(),searchinput)==0&&strcmp(usersearch.c_str(),"type")==0)||
           (strcmp(kardashiansVector[index].instafollower.c_str(),searchinput)==0&&strcmp(usersearch.c_str(),"instafollower")==0))
        {
            searchresult++;
            cout<<"\n\nname: "<<kardashiansVector[index].name<<endl;
            cout<<"type: "<<kardashiansVector[index].type<<endl;
            cout<<"instafollower: "<<kardashiansVector[index].instafollower<<endl;
            cout<<"photos: "<<kardashiansVector[index].photos<<endl;
            cout<<"id: "<<kardashiansVector[index].id<<"\n\n"<<endl;
         }
    }

    if(searchresult==0)
    {
           cout<<"unfortunately no results."<<endl;
   }
}
