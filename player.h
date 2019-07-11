#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>

using namespace std;

class player{ 
  public:
    player();
    player(int ID, char* nom, double cors, double tec, double att,double dif, int med, char* clas, char* role, int char_def);
    ~player();
    
  int get_numero() {return numero;};
  char* get_nome(){return nome;};  
  double get_corsa(){return corsa;};  
  double get_tecnica(){return tecnica;};  
  double get_attacco(){return attacco;};  
  double get_difesa(){return difesa;};  
  char* get_classe() {return classe ;};
  char* get_ruolo() {return ruolo ;};
  int get_media(){return media;};
  int get_char_def(){return caratteri;};
  void set_player(int ,char *, double, double, double , double,int, char*,char*,int);  
    
  private:
  int numero;
  char nome[300];
  char classe[300];
  char ruolo[300];
  double corsa;
  double tecnica;
  double attacco;
  double difesa;
  int media;
  int caratteri;

};

#endif
