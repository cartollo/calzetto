#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "match.h"

using namespace std;


match::match(){
 corsa_diff=0.;
 tecnica_diff=0.;
 attacco_diff=0.;
 difesa_diff=0.;
 total_value=0.;
 cont2=-1;
 player tmp_player;
 //for(int i=0;i<comp*2;i++) 
   //giocatori.push_back(tmp_player); 

}


match::~match(){


}

bool match::set_values(){
  if(giocatori.size()!=comp*2){
    cout<<"ERRORE in set_values: non hai 5 giocatori per la squadra!!!   numero giocatori caricati="<<giocatori.size()<<endl;
    return true;
  }

  corsa_diff=0.;
  tecnica_diff=0.;
  attacco_diff=0.;
  difesa_diff=0.;
  total_value=0.;
  
  for(int i=0;i<comp;i++){
    corsa_diff+=giocatori[i].get_corsa()-giocatori[i+comp].get_corsa();
    tecnica_diff+=giocatori[i].get_tecnica()-giocatori[i+comp].get_tecnica();
    attacco_diff+=giocatori[i].get_attacco()-giocatori[i+comp].get_attacco();
    difesa_diff+=giocatori[i].get_difesa()-giocatori[i+comp].get_difesa();
  }
   total_value=corsa_diff+tecnica_diff+attacco_diff+difesa_diff;
   
   // fisso i valori della partita con zero scambi per poterli utilizzare nelle fnz di scambio giocatori: 
   corsa0=corsa_diff;
   tecnica0=tecnica_diff;
   attacco0=attacco_diff;
   difesa0=difesa_diff;
   total0=total_value;
   

  return false;
}


bool match::read_list(){
  fstream input;
  input.open("players_list.txt", ios::in);
  double tec, velo,att,dif, meddouble; 
  int ID,pres, cont=0, char_def, med;
  char tmp_char[300],clas[300], role[300];
  string classe;
  string trash;
  player tmp_player;
  if(!(input.eof()))
  cout<<endl<<"Ho aperto il file"<<endl<<endl;
  else{
    cout<<"Errore apertura file!!!"<<endl;
    return true;
  }  
  while(!(input.eof())){
    if(cont2<0) {for(int i=0;i<8;i++) input>>trash;}
      cont2++;
     input>>pres>>ID>>tmp_char>>velo>>tec>>att>>dif>>med>>clas>>role>>char_def;
     if(pres>0){
        
   meddouble=(velo + tec + att + dif)/4 + 0.5;
   med=meddouble;
   if (med>=80)           sprintf(clas,"A");
   if (med<80 && med>=75) sprintf(clas,"B");
   if (med<75 && med>=70) sprintf(clas,"C");
   if (med<70 && med>=65) sprintf(clas,"D");
   if (med<65 && med>=60) sprintf(clas,"E");
   if (med<60)            sprintf(clas,"F");

         giocatori.push_back(tmp_player);
       //~ tmp_player.set_player(tmp_char,velo,tec,tatt);
       giocatori[cont].set_player(ID,tmp_char,velo,tec,att,dif,med,clas,role,char_def);
       cont++;
     }     
    
    }
  input.close();  

cout<<"Giocatori presenti: "<<cont2<<endl<<endl;

  if(giocatori.size()!=10){
    cout<<"ERRORE in read_list: non hai 5 giocatori per la squadra!!! il numero di giocatori caricati è "<<giocatori.size()<<endl;
    return true;
  }

return false;
}


void match::cout_match(){
  if(giocatori.size()!=comp*2){
     cout<<"ERROR in cout_team::: SQUADRE INCOMPLETE!!!"<<endl;
     cout<<endl; }
/*  cout<<"corsa_diff="<<corsa_diff<<endl;
  cout<<"tecnica diff="<<tecnica_diff<<endl;
  cout<<"attacco diff="<<attacco_diff<<endl;
  cout<<"difesa diff="<<difesa_diff<<endl;
  cout<<"TOTAL VALUE="<<total_value<<endl<<endl; */
  cout<<"Giocatori selezionati: "<<endl<<endl;
  for(int i=0;i<giocatori.size();i++){
      cout<<" ";
   if(i<9) cout<<" "; 
    cout<<i+1<<" "<<giocatori[i].get_nome()<<endl;
    }
   cout<<endl;
  
  return;
}
  

void match::primo_scambio(int j, int k){

  corsa_diff = corsa0 + giocatori[k].get_corsa()*2-giocatori[j].get_corsa()*2;
  tecnica_diff = tecnica0 + giocatori[k].get_tecnica()*2-giocatori[j].get_tecnica()*2;
  attacco_diff = attacco0 + giocatori[k].get_attacco()*2-giocatori[j].get_attacco()*2;
  difesa_diff = difesa0 + giocatori[k].get_difesa()*2-giocatori[j].get_difesa()*2;
  total_value = corsa_diff+tecnica_diff+attacco_diff+difesa_diff;
 
   
  return;
}



void match::secondo_scambio(int j,int k,int l, int m ){

  corsa_diff= corsa0 + giocatori[l].get_corsa()*2+giocatori[m].get_corsa()*2-giocatori[j].get_corsa()*2-giocatori[k].get_corsa()*2;
  tecnica_diff = tecnica0 + giocatori[l].get_tecnica()*2+giocatori[m].get_tecnica()*2-giocatori[j].get_tecnica()*2-giocatori[k].get_tecnica()*2;
  attacco_diff = attacco0 + giocatori[l].get_attacco()*2+giocatori[m].get_attacco()*2-giocatori[j].get_attacco()*2-giocatori[k].get_attacco()*2;
  difesa_diff = difesa0 + giocatori[l].get_difesa()*2+giocatori[m].get_difesa()*2-giocatori[j].get_difesa()*2-giocatori[k].get_difesa()*2;
  total_value=corsa_diff+tecnica_diff+attacco_diff+difesa_diff;

return;
}


void match::print_data(string data,vector<int> partita,int golA, int golB, vector<int> gol,char* commento,int commentscout)
{
 vector<string> nomi(cont2);
 vector<vector<double> > t_dati;
 vector<double> dati (14,0);
 corsa_diff=partita[0];
 tecnica_diff=partita[1];
 attacco_diff=partita[2];
 difesa_diff=partita[3];
 total_value=partita[4];
 int j=partita[5];
 int k=partita[6];
 int l=partita[7];
 int m=partita[8];
 int g=0;
 double dob=0.;

 vector<string> statistiche;
 string statistica;
 string giocatore;
 string trash;
 string database;
 char pollo;
 vector<vector<int> > squadraA;
 vector<vector<int> > squadraB;
 vector<int> row(2,0);
 vector<vector<int> > stat;

  fstream input;
  fstream output;


    for(int i=0;i<comp;i++){
  if (i!=j && i!=k){
  row[0]=giocatori[i].get_numero();
  row[1]=giocatori[i].get_media();
  squadraA.push_back(row);
  }}
  if(l!=-1){
  row[0]=giocatori[l].get_numero();
  row[1]=giocatori[l].get_media();
  squadraA.push_back(row);
  }
  if(m!=-1)
  row[0]=giocatori[m].get_numero();
  row[1]=giocatori[m].get_media();
  squadraA.push_back(row);
   


 for(int i=comp;i<comp*2;i++){
  if (i!=l && i!=m){
  row[0]=giocatori[i].get_numero();
  row[1]=giocatori[i].get_media();
  squadraB.push_back(row);
  }}
  if(j!=-1){
  row[0]=giocatori[j].get_numero();
  row[1]=giocatori[j].get_media();
  squadraB.push_back(row);
  }
  if(k!=-1)
  row[0]=giocatori[k].get_numero();
  row[1]=giocatori[k].get_media();
  squadraB.push_back(row);
   

 int max;

 for (int i=0;i<comp;i++){  //ordino squadraA
 max = i;
 for(int j=i+1; j<comp; j++)  if(squadraA[j][1] > squadraA[max][1]) max = j;

  row[0] = squadraA[max][0];
  squadraA[max][0]=squadraA[i][0];
  squadraA[i][0]=row[0];
  row[1] = squadraA[max][1];
  squadraA[max][1]=squadraA[i][1];
  squadraA[i][1]=row[1];
}

 for (int i=0;i<comp;i++){  //ordino squadraB  
 max = i;
 for(int j=i+1; j<comp; j++) if(squadraB[j][1] > squadraB[max][1]) max = j;
    
  row[0] = squadraB[max][0];
  squadraB[max][0]=squadraB[i][0];
  squadraB[i][0]=row[0];
  row[1] = squadraB[max][1];
  squadraB[max][1]=squadraB[i][1];
  squadraB[i][1]=row[1];
}   





for(int i=0;i<4;i++){
   row[0]=i;
   row[1]=partita[i];
   stat.push_back(row);
   }

 for (int i=0;i<4;i++){  //ordino stat  
 max = i;
 for(int j=i+1; j<4; j++) if(stat[j][1] > stat[max][1]) max = j;
    
  row[0] = stat[max][0];
  stat[max][0]=stat[i][0];
  stat[i][0]=row[0];
  row[1] = stat[max][1];
  stat[max][1]=stat[i][1];
  stat[i][1]=row[1];
}  



  input.open("players_list.txt", ios::in);
  vector<int> pres(cont2+1,0);
  double tec, velo,att,dif, meddouble; 
  int ID, cont=0, char_def, med;
  char tmp_char[300],clas[300], role[300];
  string classe;
  player tmp_player;
 
 
  while(!(input.eof())){
    if(cont==0) for(int i=0;i<8;i++) input>>trash;
     input>>pres[cont]>>ID>>tmp_char>>velo>>tec>>att>>dif>>med>>clas>>role>>char_def;
    
  for(int j=0;j<comp;j++){     
   if(ID==squadraA[j][0]){
    for(int i=0;i<4;i++){
      if(golA-golB>i){
          if(stat[3-i][0]==0){ velo++;if(j==0){ statistica="Corsa",statistiche.push_back(statistica);}}
          if(stat[3-i][0]==1){ tec++;if(j==0) {statistica="Tecnica",statistiche.push_back(statistica);}}
          if(stat[3-i][0]==2){ att++;if(j==0) {statistica="Attacco",statistiche.push_back(statistica);}}
          if(stat[3-i][0]==3){ dif++;if(j==0){ statistica="Difesa",statistiche.push_back(statistica);}} 
             }
      if(golA-golB<-i){
          if(stat[i][0]==0) velo--;
          if(stat[i][0]==1) tec--;
          if(stat[i][0]==2) att--;
          if(stat[i][0]==3) dif--;   
             }
            }}
   if(ID==squadraB[j][0]){
    for(int i=0;i<4;i++){
      if(golB-golA>i){
          if(stat[i][0]==0){ velo++;if(j==0){ statistica="Corsa",statistiche.push_back(statistica);}}
          if(stat[i][0]==1){ tec++;if(j==0){ statistica="Tecnica",statistiche.push_back(statistica);}}
          if(stat[i][0]==2){ att++;if(j==0) {statistica="Attacco",statistiche.push_back(statistica);}}
          if(stat[i][0]==3){ dif++;if(j==0){ statistica="Difesa",statistiche.push_back(statistica);}}    
             }
      if(golB-golA<-i){
          if(stat[3-i][0]==0) velo--;
          if(stat[3-i][0]==1) tec--;
          if(stat[3-i][0]==2) att--;
          if(stat[3-i][0]==3) dif--;   
             }
            }}}

   meddouble=(velo + tec + att + dif)/4 + 0.5;
   med=meddouble;
   if (med>=80)           sprintf(clas,"A");
   if (med<80 && med>=75) sprintf(clas,"B");
   if (med<75 && med>=70) sprintf(clas,"C");
   if (med<70 && med>=65) sprintf(clas,"D");
   if (med<65 && med>=60) sprintf(clas,"E");
   if (med<60)            sprintf(clas,"F");

      tutti.push_back(tmp_player);
       //~ tmp_player.set_player(tmp_char,velo,tec,tatt);
       tutti[cont].set_player(ID,tmp_char,velo,tec,att,dif,med,clas,role,char_def);
       cont++;
          
    
    }
  input.close();  



    output.open("players_list.txt", ios::out);
    output<<endl;
   output<<"Giocatore         Vel Tec Att Dif Tot Cl Rol"<<endl<<endl;
    for(int i=0;i<tutti.size()-1;i++){
      output<<pres[i]<<"  ";
      if(i<9)output<<"0";
      output<<tutti[i].get_numero()<<" ";
      output<<tutti[i].get_nome()<<"    ";
      for(int j=0;j<tutti[i].get_char_def();j++) output<<" ";
      output<<tutti[i].get_corsa()<<"  ";
      output<<tutti[i].get_tecnica()<<"  ";
      output<<tutti[i].get_attacco()<<"  ";
      output<<tutti[i].get_difesa()<<"  ";
      output<<tutti[i].get_media()<<"  ";
      output<<tutti[i].get_classe()<<"  ";
      output<<tutti[i].get_ruolo()<<"  ";
      output<<tutti[i].get_char_def()<<"  ";
      output<<endl;
      }
 output<<0;
output.close();

   input.open("database.txt", ios::in);
   
while(!(input.eof())){  
 for(int i=0;i<14;i++) 
   input>>trash;

 for(int i=0;i<cont2;i++){ // creo tabella partite gol ecc ecc
    input>>dati[0];
    input>>nomi[i];
    for(int h=0;h<13;h++) 
      input>>dati[h+1];
    t_dati.push_back(dati);
    }


 for(int i=0;i<cont2;i++){

  for(int h=0;h<5;h++){
   if (squadraA[h][0]==t_dati[i][0]){
       if (golA>golB){
         t_dati[i][1]++;
         t_dati[i][2]++;}
       if (golA==golB){
         t_dati[i][1]++;
         t_dati[i][4]++;}
       if (golA<golB){
         t_dati[i][1]++;
         t_dati[i][3]++;}
  
      dob=(t_dati[i][2]/t_dati[i][1])*100+0.5;
      g=dob;
      t_dati[i][5]=g;
      dob=(t_dati[i][3]/t_dati[i][1])*100+0.5;
      g=dob;
      t_dati[i][6]=g;
      dob=(t_dati[i][4]/t_dati[i][1])*100+0.5;
      g=dob;
      t_dati[i][7]=g;
      t_dati[i][10]=t_dati[i][10]+golA;
      t_dati[i][11]=t_dati[i][11]+golB;
      t_dati[i][12]=t_dati[i][10]-t_dati[i][11];
  
           for(int j=0; j<comp*2;j++){
           if (t_dati[i][0]==giocatori[j].get_numero()){
            t_dati[i][8]=t_dati[i][8] +gol[j]; 
            dob=(t_dati[i][8]/t_dati[i][1])*100+0.5;
            g=dob;
            dob=g; 
            t_dati[i][9]=dob/100;
          giocatore=giocatori[j].get_nome();
           for(int y=0;y<babbi.size();y++) if (babbi[y]==giocatore) t_dati[i][13]++;
            }}
  
       }
        
    
  
   if (squadraB[h][0]==t_dati[i][0]){
     if (golA<golB){
       t_dati[i][1]++;
       t_dati[i][2]++;}
     if (golA==golB){
       t_dati[i][1]++;
       t_dati[i][4]++;}
     if (golA>golB){
       t_dati[i][1]++;
       t_dati[i][3]++;}
  
     dob=(t_dati[i][2]/t_dati[i][1])*100+0.5;
     g=dob;
     t_dati[i][5]=g;
     dob=(t_dati[i][3]/t_dati[i][1])*100+0.5;
     g=dob;
     t_dati[i][6]=g;
     dob=(t_dati[i][4]/t_dati[i][1])*100+0.5;
     g=dob;
     t_dati[i][7]=g;
     t_dati[i][11]=t_dati[i][11]+golA;
     t_dati[i][10]=t_dati[i][10]+golB;
     t_dati[i][12]=t_dati[i][10]-t_dati[i][11];
  
     for(int j=0; j<comp*2;j++){
         if (t_dati[i][0]==giocatori[j].get_numero()){
           t_dati[i][8]=t_dati[i][8] +gol[j]; 
           dob=(t_dati[i][8]/t_dati[i][1])*100+0.5;
           g=dob;
           dob=g; 
           t_dati[i][9]=dob/100;
           giocatore=giocatori[j].get_nome();
           for(int y=0;y<babbi.size();y++) 
             if (babbi[y]==giocatore) 
               t_dati[i][13]++;
        }
      }
   } 
       }
   }

 

   
   getline(input,database,pollo);

}//fine lettura database.txt
 input.close();

   
 output.open("database.txt", ios::out);
   
 ios init(NULL);
 init.copyfmt(cout);   
 output<<endl<<"  Giocatore       PG    Win    Loss   Draw    Wi%    Lo%    Dr%    GF*    MG*     GFs   GSs    DRs    Gio "<<endl<<endl;
 for(int i=0; i<cont2; i++){
   output<<"  ";
   if(i<9) 
     output<<"0";
   output<<t_dati[i][0]<<" "<<nomi[i]<<"    ";
   g=tutti[i].get_char_def();
   for(int j=0;j<g;j++) output<<" ";   
   for(int h=0;h<13;h++)
     output<< setw(3)<<t_dati[i][h+1]<<"    ";
   output<<endl;   
 }
 output.copyfmt(init);
   
    output<<database; //incollo databese vecchio
    
    output<<data<<endl;




output<<"Squadra A"<<" gol= "<<golA<<"              		   Squadra B"<<" gol= "<<golB<<endl;
for(int i=0;i<comp;i++) { 
 for(int j=0; j<comp*2;j++){
 if (squadraA[i][0]==giocatori[j].get_numero()){
 output<<giocatori[j].get_nome()<<"  ";
 for(int h=0;h<giocatori[j].get_char_def();h++) output<<" ";
 if(gol[j]!=0) output<<"gol= "<<gol[j]<<" ";
 else output<<"       ";
 output<<" ("<<giocatori[j].get_classe()<<")"<<" "<<"["<<giocatori[j].get_media()<<"]"<<" "<<"{"<<giocatori[j].get_ruolo()<<"}";
 output<<"           ";}}
 
 for(int j=0; j<comp*2;j++){
 if (squadraB[i][0]==giocatori[j].get_numero()){
 output<<giocatori[j].get_nome()<<"  ";
 for(int h=0;h<giocatori[j].get_char_def();h++) output<<" ";
  if(gol[j]!=0) output<<"gol= "<<gol[j]<<" ";
  else output<<"       ";
 output<<" ("<<giocatori[j].get_classe()<<")"<<" "<<"["<<giocatori[j].get_media()<<"]"<<" "<<"{"<<giocatori[j].get_ruolo()<<"}";
 output<<"           ";}}

 output<<endl;
}
output<<endl;
    output<<"Corsa:"<<corsa_diff<<"     ";
    output<<"Tecnica:"<<tecnica_diff<<"     ";
    output<<"Attacco:"<<attacco_diff<<"     ";
    output<<"Difesa:"<<difesa_diff<<"     ";
    output<<"Totale:"<<total_value<<"     ";
    output<<endl<<endl; 
  if(commentscout>0)  output<<commento<<endl<<endl;
    output<<"Statistiche aggiornate:";
  if(statistiche.size()>0) {
  for(int i=0;i<statistiche.size();i++){ 
    output<<" "<<statistiche[i] ;
    if(i<statistiche.size()-1) 
      output<<",";
    else 
      output<<".";
    }
  }
    output<<endl<<endl;
    output<<"  Giocatore      Vel Tec Att Dif Tot Cl Rol"<<endl<<endl;;
    
    for(int i=0;i<tutti.size()-1;i++){
      output<<"  ";
      if(i<9)output<<"0";
      output<<tutti[i].get_numero()<<" ";
      output<<tutti[i].get_nome()<<"    ";
      for(int j=0;j<tutti[i].get_char_def();j++) output<<" ";
      output<<tutti[i].get_corsa()<<"  ";
      output<<tutti[i].get_tecnica()<<"  ";
      output<<tutti[i].get_attacco()<<"  ";
      output<<tutti[i].get_difesa()<<"  ";
      output<<tutti[i].get_media()<<"  ";
      output<<tutti[i].get_classe()<<"  ";
      output<<tutti[i].get_ruolo()<<"  ";
      output<<endl;
      }
     output<<endl;


output.close();    

return;
}

void match::pronostico(vector<int> partita)
{
 int a=5,b=5;
 int velA=0,tecA=0,attA=0,difA=0,totA=0, midA=0;
 int velB=0,tecB=0,attB=0,difB=0,totB=0, midB=0;
 double mid;
 corsa_diff=partita[0];
 tecnica_diff=partita[1];
 attacco_diff=partita[2];
 difesa_diff=partita[3];
 total_value=partita[4];
 int j=partita[5];
 int k=partita[6];
 int l=partita[7];
 int m=partita[8];


    for(int i=0;i<comp;i++){
  if (i!=j && i!=k){
 velA=velA+giocatori[i].get_corsa();
 tecA=tecA+giocatori[i].get_tecnica();
 attA=attA+giocatori[i].get_attacco();
 difA=difA+giocatori[i].get_difesa();
  }}
  if(l!=-1){
 velA=velA+giocatori[l].get_corsa();
 tecA=tecA+giocatori[l].get_tecnica();
 attA=attA+giocatori[l].get_attacco();
 difA=difA+giocatori[l].get_difesa();
  }
  if(m!=-1){
 velA=velA+giocatori[m].get_corsa();
 tecA=tecA+giocatori[m].get_tecnica();
 attA=attA+giocatori[m].get_attacco();
 difA=difA+giocatori[m].get_difesa();
 }
   
 totA=velA+tecA+attA+difA;
 
 velB=velA-corsa_diff;
 tecB=tecA-tecnica_diff;
 attB=attA-attacco_diff;
 difB=difA-difesa_diff;
 totB=totA-total_value;
 mid=totA/4+0.5;
 midA=mid;
 mid=totB/4+0.5;
 midB=mid;

 for(int i=1;i<5;i++){
 if(attA-difB>i*(10+i)-5) a++;
 if(attB-difA>i*(10+i)-5) b++;
 if(difA-attB>i*(10+i)-5) b--;
 if(difB-attA>i*(10+i)-5) a--;
 if(tecA-difB>i*(10+i)-5) a++;
 if(tecB-difA>i*(10+i)-5) b++;
 if(total_value>i*(10+i)-5) a++;
 if(total_value<-i*(10+i)-5) b++;
 if(corsa_diff>i*(10+i)-5) a++;
 if(corsa_diff<-i*(10+i)-5) b++;
 if(velA<355-i*(10+i)) b++;
 if(velB<355-i*(10+i)) a++;
 }

 if(a<0)a=0;
 if(b<0)b=0;
 
cout<<"Previsione del risulatato: "<<a<<"-"<<b<<endl<<endl;
cout<<"            "<<"Vel "<<"Tec "<<"Att "<<"Dif "<<"Tot "<<endl<<endl;
cout<<"Squadra A:  "<<velA<<" "<<tecA<<" "<<attA<<" "<<difA<<" "<<midA<<endl<<endl;
cout<<"squadra B:  "<<velB<<" "<<tecB<<" "<<attB<<" "<<difB<<" "<<midB<<endl<<endl;

return;
}

void  match::score(int i){
 goal=0;
 string giocatore = giocatori[i].get_nome();
 cout<<"Quanti gol ha segnato "<<giocatori[i].get_nome()<<"? ";
 cin>>goal; 
 if (giocatore=="Gio" && goal>0){ 
   cout<<"Fermi tutti! Non ci credo!! chi l'ha preso da GIO!? ";
   for (int i=0;i<goal;i++){
     cin>>babbo;
     babbi.push_back(babbo);
     if (i<goal-1) 
       cout<<"E poi?! ";
   }
 }
return;
}



void match::stampa_top (int j,int k,int l,int m){
  
vector<int> row(2,0);
vector<vector<int> > squadraA;
vector<vector<int> > squadraB;


 for(int i=0;i<comp;i++){
  if (i!=j && i!=k){
  row[0]=giocatori[i].get_numero();
  row[1]=giocatori[i].get_media();
  squadraA.push_back(row);
  }}
  if(l!=-1){
  row[0]=giocatori[l].get_numero();
  row[1]=giocatori[l].get_media();
  squadraA.push_back(row);
  }
  if(m!=-1)
  row[0]=giocatori[m].get_numero();
  row[1]=giocatori[m].get_media();
  squadraA.push_back(row);
   


 for(int i=comp;i<comp*2;i++){
  if (i!=l && i!=m){
  row[0]=giocatori[i].get_numero();
  row[1]=giocatori[i].get_media();
  squadraB.push_back(row);
  }}
  if(j!=-1){
  row[0]=giocatori[j].get_numero();
  row[1]=giocatori[j].get_media();
  squadraB.push_back(row);
  }
  if(k!=-1)
  row[0]=giocatori[k].get_numero();
  row[1]=giocatori[k].get_media();
  squadraB.push_back(row);
   

 int max;

 for (int i=0;i<comp;i++){  //ordino squadraA
 max = i;
 for(int j=i+1; j<comp; j++)  if(squadraA[j][1] > squadraA[max][1]) max = j;

  row[0] = squadraA[max][0];
  squadraA[max][0]=squadraA[i][0];
  squadraA[i][0]=row[0];
  row[1] = squadraA[max][1];
  squadraA[max][1]=squadraA[i][1];
  squadraA[i][1]=row[1];
}

 for (int i=0;i<comp;i++){  //ordino squadraB  
 max = i;
 for(int j=i+1; j<comp; j++) if(squadraB[j][1] > squadraB[max][1]) max = j;
    
  row[0] = squadraB[max][0];
  squadraB[max][0]=squadraB[i][0];
  squadraB[i][0]=row[0];
  row[1] = squadraB[max][1];
  squadraB[max][1]=squadraB[i][1];
  squadraB[i][1]=row[1];
}


cout<<"Squadra A"<<"             		   "<<"Squadra B"<<endl;
for(int i=0;i<comp;i++) { 
 for(int j=0; j<comp*2;j++){
 if (squadraA[i][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome()<<" ";
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" ("<<giocatori[j].get_classe()<<")"<<" "<<"["<<giocatori[j].get_media()<<"]"<<" "<<"{"<<giocatori[j].get_ruolo()<<"}";
 cout<<"           ";}}
 
 for(int j=0; j<comp*2;j++){
 if (squadraB[i][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome()<<" ";
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" ("<<giocatori[j].get_classe()<<")"<<" "<<"["<<giocatori[j].get_media()<<"]"<<" "<<"{"<<giocatori[j].get_ruolo()<<"}";
 cout<<"           ";}}

 cout<<endl;
}
cout<<endl;
return;

}

void match::team_maker (int* j,int* k,int* l,int* m){
 vector<int> squadra(5,0);
 int c=0,c2=0, ca=0,cb=5,t=0;
 int mille=1000;
 cout<<"Benvenuto nella modalità Team Maker!"<<endl<<endl;
 cout<<"Giocatori selezionati:"<<endl<<endl;
 for(int i=0;i<10;i++){
  cout<<" ";
  if(giocatori[i].get_numero()<10) cout<<0;
   cout<<giocatori[i].get_numero()<<" "<<giocatori[i].get_nome()<<endl;
                      }
 cout<<endl;
 cout<< "Inserisci ID dei giocatori di una delle due squadre: ";
 for(int i=0;i<comp;i++) cin>>squadra[i];



 for(int i=0;i<comp;i++){ //check presenza giocatori
  c=0;
  for(int h=0;h<comp*2;h++){ if(squadra[i]==giocatori[h].get_numero()) c++;}
       if(c==0){ 
        cout<<endl<<"Errore:'"<<squadra[i]<<"' non corrisponde a nessun giocatore selezionato"<<endl<<endl;    
        *j=mille;
        return;
           }}

            
  for(int i=0;i<comp;i++){
   for(int h=0;h<comp;h++){
    	if(squadra[h]==giocatori[i].get_numero()){
           ca++;
           cb--;
                          }}}
  
  if (ca>cb) { 
     c=0;
     c2=0;
     
     for(int i=0;i<comp;i++){
        t=0;
        for(int h=0;h<comp;h++){
          if(squadra[h]==giocatori[i].get_numero()) t++;
          if(squadra[h]==giocatori[i+comp].get_numero()){
             if(c2>0) *m=i+comp;
             if (c2==0){
               *l=i+comp;
               c2++;
                 }}}
                 
                 
            if (t==0){
		if(c>0) *k=i;
                if (c==0){
                *j=i;
                c++;
                 }}}}
		


   if (ca<cb) { 
     c=0;
     c2=0;
     for(int i=0;i<comp;i++){
      t=0;
       for(int h=0;h<comp;h++){
          if(squadra[h]==giocatori[i+comp].get_numero()) t++;    
          if(squadra[h]==giocatori[i].get_numero()){
            if (c>0) *k=i;
            if (c==0){
               *j=i;
               c++;
                 }}}
                 
		 
             if (t==0){
                if (c2>0) *m=i+comp;
                if (c2==0){
                  *l=i+comp;
                   c2++;
                      }}}}
                  
     cout<<endl;            

     
return;
}


/*

void match::snakesort(){

 vector<int> row(2,0);
 vector<vector<int> > snake;

 corsa_diff=0;
 tecnica_diff=0;
 tattica_diff=0;
 total_value=0;

 for(int i=0;i<comp*2;i++){ //carico snake
  row[0]=giocatori[i].get_numero();
  row[1]=giocatori[i].get_media();
  snake.push_back(row);}
 int max;
 for(int i=0;i<comp*2;i++){ //ordino snake
  max = i;
  for(int j=i+1; j<comp*2; j++)  if(snake[j][1] > snake[max][1]) max = j;
  row[0] = snake[max][0];
  snake[max][0]=snake[i][0];
  snake[i][0]=row[0];
  row[1] = snake[max][1];
  snake[max][1]=snake[i][1];
  snake[i][1]=row[1];
  }

cout<<"Partita 'Snakesort':"<<endl<<endl;
cout<<"Squadra A"<<"             		   "<<"Squadra B"<<endl;

 for(int j=0; j<comp*2;j++){
 if (snake[0][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome();
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" (class "<<giocatori[j].get_classe()<<")"<<" "<<"("<<giocatori[j].get_ruolo()<<")";
 cout<<"           ";
    corsa_diff+=giocatori[j].get_corsa();
    tecnica_diff+=giocatori[j].get_tecnica();
    tattica_diff+=giocatori[j].get_tattica();
}}
 
 for(int j=0; j<comp*2;j++){
 if (snake[1][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome();
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" (class "<<giocatori[j].get_classe()<<")"<<" "<<"("<<giocatori[j].get_ruolo()<<")";
 cout<<endl;
    corsa_diff-=giocatori[j].get_corsa();
    tecnica_diff-=giocatori[j].get_tecnica();
    tattica_diff-=giocatori[j].get_tattica();

}}


 for(int i=2;i<comp*2-1;i+=2){
 for(int j=0; j<comp*2;j++){
 if (snake[i+1][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome();
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" (class "<<giocatori[j].get_classe()<<")"<<" "<<"("<<giocatori[j].get_ruolo()<<")";
 cout<<"           ";
     corsa_diff+=giocatori[j].get_corsa();
     tecnica_diff+=giocatori[j].get_tecnica();
     tattica_diff+=giocatori[j].get_tattica();
 }}
 
 for(int j=0; j<comp*2;j++){
 if (snake[i][0]==giocatori[j].get_numero()){
 cout<<giocatori[j].get_nome();
 for(int h=0;h<giocatori[j].get_char_def();h++) cout<<" ";
 cout<<" (class "<<giocatori[j].get_classe()<<")"<<" "<<"("<<giocatori[j].get_ruolo()<<")";
 cout<<endl;
    corsa_diff-=giocatori[j].get_corsa();
    tecnica_diff-=giocatori[j].get_tecnica();
    tattica_diff-=giocatori[j].get_tattica();
}}
}

 total_value=corsa_diff+tecnica_diff+tattica_diff;
 cout<<endl;

    cout<<"la differenza di corsa tra squadra A e B è "<<corsa_diff<<endl;
    cout<<"la differenza di tecnica tra squadra A e B è "<<tecnica_diff<<endl;
    cout<<"la differenza di tattica tra squadra A e B è "<<tattica_diff<<endl;
    cout<<"la differenza di valore totale tra squadra A e B è "<<total_value<<endl;
    cout<<endl; 
   
 
 return;
 }
  
*/



