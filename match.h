#ifndef MATCH_H
#define MATCH_H

#define comp 5

#include <iostream>
#include <fstream>
#include <vector>
#include "player.h"

using namespace std;

class match{
  
  public:
    match();
    ~match();
  
  //getters
  int get_corsa_diff(){return corsa_diff;};
  int get_tecnica_diff(){return tecnica_diff;};
  int get_attacco_diff(){return attacco_diff;};
  int get_difesa_diff(){return difesa_diff;};
  int get_total_value(){return total_value;}
  int get_score(){return goal;};
  player get_player(int i){return giocatori[i];};
  
  //altre funz
  bool set_values();//setta la differenza di valore di queste due squadre  
  void cout_match();//per stampare la squadra e i valori
  bool read_list();//lettura di players_list per caricare parametri e giocatori  
  void primo_scambio(int j, int k);
  void secondo_scambio(int j, int k,int l,int m);
  void stampa_top(int i,int j,int k,int l);
  void print_data(string data,vector<int> partita,int golA, int golB, vector<int> gol,char* commento,int commentscout);
  void score(int i);
  void snakesort();
  void pronostico(vector<int> partita);
  void team_maker(int* j, int* k, int* l, int* m);

  int corsa_diff;//differenza di corsa tra i primi 5 e gli ultimi 5
  int tecnica_diff;
  int attacco_diff;
  int difesa_diff;
  int total_value;
  int corsa0;
  int tecnica0;
  int attacco0;
  int difesa0;
  int total0;
  int goal;
  int cont2;
  vector<string> babbi;
  string babbo;

  
  vector<player> giocatori;//vettore con tutti i giocatori
  vector<player> tutti;

  

};

#endif
