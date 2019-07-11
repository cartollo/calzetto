#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "match.h"
#include "player.h"


using namespace std;

  
int main(int argc, char * argv[]) {

match partita;

if(partita.read_list())//leggo file
  return 0;

vector<vector<int> > matrice;
vector<int> row(9,0);
vector<vector<int> > matricebuone;
vector<int> gol(10,0);


//matriciozza: 8 elementi per riga, primi 4    corsa, tecnica, tattica e total_value gli altri per scambi (2+2)
//per i scambi il primo c'è sempre , il secondo se negativo non c'è
//primo elemento è -1-1-1-1 che è schieramento iniziale


//cicli for per scambi, richiamando in match un metodo scambi_calcola() gli passiamo 3 &double per corsa tecnica etc., e due/uno int per posizione scambiata, lui qua calcola le differnze e le salva nei tre double, i tre double li mettiamo in una matrice;



//prova 
partita.set_values(); // con questo riempiamo la prima riga della matriciozza
partita.cout_match();  


row[0]=partita.get_corsa_diff();
row[1]=partita.get_tecnica_diff();
row[2]=partita.get_attacco_diff();
row[3]=partita.get_difesa_diff();
row[4]=partita.get_total_value();
row[5]=-1;
row[6]=-1;
row[7]=-1;
row[8]=-1;
matrice.push_back(row); // zero scambi, 1 squadra


 for (int i=0;i<5;i++){          //primo scambio, 26 squadre
   for (int j=5;j<10;j++){
	partita.primo_scambio(i,j);
	row[0]=partita.get_corsa_diff();
        row[1]=partita.get_tecnica_diff();
        row[2]=partita.get_attacco_diff();
        row[3]=partita.get_difesa_diff();
	row[4]=partita.get_total_value();
	row[5]=i;
	row[6]=-1;
	row[7]=j;
	row[8]=-1;
	matrice.push_back(row);
	}}

 for (int i=0;i<5;i++){          //secondo scambio, 126 squadre
   for (int j=i+1;j<5;j++){  
     for (int k=5;k<10;k++){
        for (int l=k+1;l<10;l++){

	partita.secondo_scambio(i,j,k,l);
	row[0]=partita.get_corsa_diff();
        row[1]=partita.get_tecnica_diff();
        row[2]=partita.get_attacco_diff();
        row[3]=partita.get_difesa_diff();
	row[4]=partita.get_total_value();;
	row[5]=i;
	row[6]=j;
	row[7]=k;
	row[8]=l;
	matrice.push_back(row);
	}}}}




for (int i=0;i<matrice.size();i++){ //seleziono le squadre sui 4 parametri (corsa,tec,tat e tot) 
  if ((pow(pow(matrice[i][0],2),0.5) < 21) 
     && (pow(pow(matrice[i][1],2),0.5) < 21)
      && (pow(pow(matrice[i][2],2),0.5) < 21)
       && (pow(pow(matrice[i][3],2),0.5) < 21) 
        && (pow(pow(matrice[i][4],2),0.5) < 21)){
	         for(int k=0;k<9;k++) row[k]=(matrice[i][k]);

     matricebuone.push_back(row);}
}


if (matricebuone.size()==0){
 cout<<"Attenzione!! Nessuna partita ha superato i criteri di selezione!"<<endl<<endl;
 return 0;
   }

cout<<"Partite selezionate: "<<matricebuone.size()<<endl<<endl;


 int min;

 for (int i=0;i<matricebuone.size()-1;i++){  //ordino matricebuone per valore assoluto crescente di valore tot
   
 min = i;

 for(int j=i+1; j<matricebuone.size(); j++)
  if(pow(pow(matricebuone[j][4],2),0.5) < pow(pow(matricebuone[min][4],2),0.5))
    min = j;

  for (int k=0;k<9;k++){
  row[k]=matricebuone[min][k];
  matricebuone[min][k]=matricebuone[i][k];
  matricebuone[i][k]=row[k];
  }

}



 for(int i=0;i<3;i++) {   //stampo le prime 3 combinazioni
    if(matricebuone.size()>i){
    cout<<"Partita "<<i+1<<")"<<endl<<endl;
    partita.stampa_top(matricebuone[i][5],matricebuone[i][6],matricebuone[i][7],matricebuone[i][8]);
    cout<<"Corsa:"<<matricebuone[i][0]<<"    ";
    cout<<"Tecnica:"<<matricebuone[i][1]<<"    ";
    cout<<"Attacco:"<<matricebuone[i][2]<<"    ";
    cout<<"Difesa:"<<matricebuone[i][3]<<"    ";
    cout<<"Totale:"<<matricebuone[i][4]<<"    ";
    cout<<endl<<endl;;    
    }}
    
string sn;
string data;
 int j=3;
while (j<matricebuone.size() && j>0){
   cout<<"Vuoi che ti proponga un'altra partita? (s/n) "<<endl;
   cin>>sn;
   cout<<endl;
   if (sn=="s"){
    cout<<"Partita "<<j+1<<")"<<endl<<endl;
    partita.stampa_top(matricebuone[j][5],matricebuone[j][6],matricebuone[j][7],matricebuone[j][8]);
    cout<<"Corsa:"<<matricebuone[j][0]<<"    ";
    cout<<"Tecnica:"<<matricebuone[j][1]<<"    ";
    cout<<"Attacco:"<<matricebuone[j][2]<<"    ";
    cout<<"Difesa:"<<matricebuone[j][3]<<"    ";
    cout<<"Totale:"<<matricebuone[j][4]<<"    ";
    cout<<endl<<endl; 
    j++;
    }
 else j=0  ;
}



if(j>matricebuone.size()-1) {cout<<"Non ci sono altre partite disponibili"<<endl<<endl; }

/*
cout<<"Vuoi che ti stampi la partita 'Snakesort'? (s/n) ";
cin>>sn;
cout<<endl;
if (sn=="s") partita.snakesort();
*/
int commentscout=0;
int comb=-1,golA,golB;
char commento[500];
cout<<"Quale combinazione di squadre avete scelto? (numero) "<<endl;
cin>>comb;
cout<<endl;
if(comb<0 or comb>matricebuone.size()){
cout<<"Error: '"<<comb<<"' non corrisponde a nessuna delle partite disponibili."<<endl<<endl; 
return 0;}

if(comb==0){
        int j=-1,k=-1,l=-1,m=-1;
        partita.team_maker(&j,&k,&l,&m);
        if(j==1000) return 0;
        if(j==-1 && k==-1) partita.set_values();
        if (k==-1 && j!=-1) partita.primo_scambio(j,l);
        if (k!=-1) partita.secondo_scambio(j,k,l,m);
	row[0]=partita.get_corsa_diff();
        row[1]=partita.get_tecnica_diff();
        row[2]=partita.get_attacco_diff();
        row[3]=partita.get_difesa_diff();
	row[4]=partita.get_total_value();
	row[5]=j;
	row[6]=k;
	row[7]=l;
	row[8]=m;
 
    partita.stampa_top(j,k,l,m);
    cout<<"Corsa:"<<partita.get_corsa_diff()<<"    ";
    cout<<"Tecnica:"<<partita.get_tecnica_diff()<<"    ";
    cout<<"Attacco:"<<partita.get_attacco_diff()<<"    ";
    cout<<"Difesa:"<<partita.get_difesa_diff()<<"    ";
    cout<<"Totale:"<<partita.get_total_value()<<"    ";
    cout<<endl<<endl;


    

         }


if(comb>0) { for(int i=0;i<9;i++) row[i]= matricebuone[comb-1][i];}

partita.pronostico(row);
cout<< "Hai già giocato la partita? (s/n) "<<endl;
cin>>sn;
cout<<endl;
if (sn!="s") return 0;
cout<<"In quale data? (gg/mm/aa) "<<endl;
cin>>data; 
cout<<endl;
cout<<"Punteggio finale della squadra A: "<<endl;
cin>>golA;
cout<<endl;
cout<<"Punteggio finale della squadra B: "<<endl;
cin>>golB;
cout<<endl;
for(int i=0;i<10;i++){
  partita.score(i);   
  gol[i]=partita.get_score();
}
cout<<endl;
cout<<"Commenti sulla partita? (s/n) "<<endl;
cin>>sn;

if (sn=="s"){
commentscout=1;
cout<<endl;
cout<<"Scivi le note da ricordare: "<<endl;
cin.getline (commento,500);
cin.getline (commento,500);
}
cout<<endl;



partita.print_data(data,row,golA,golB,gol,commento,commentscout);







return 0;
}


