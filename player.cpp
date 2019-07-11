#include <iostream>
#include <fstream>
#include <cstring>

#include "player.h"


using namespace std;


player::player(){
 numero = 0;
 sprintf(nome,"anonimo");
 sprintf(classe,"X");
 sprintf(ruolo,"nor");
 corsa=0;
 tecnica=0;
 attacco=0;
 difesa=0;
 media =0;
 caratteri =0;
}

player::player(int ID,char* nom, double cors, double tec, double att,double dif,int med,char* clas,char* role, int char_def){
  numero=ID;
  strcpy(nome,nom);
  strcpy(classe, clas);
  strcpy(ruolo, role);
  corsa=cors;
  tecnica=tec;
  attacco=att;
  difesa=dif;
  media =med;
  caratteri=char_def;
}

player::~player(){


}

void player::set_player(int inID,char *inname, double incorsa, double intecnica, double inattacco,double indifesa, int inmed, char* inclas,char* inrole,int inchar_def){
numero=inID;
strcpy(nome, inname);
strcpy(classe,inclas);
strcpy(ruolo, inrole);
corsa=incorsa;
tecnica=intecnica;
attacco=inattacco;
difesa=indifesa;  
media=inmed;
caratteri=inchar_def;

return;  
}

  

