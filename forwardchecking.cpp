using namespace std;
#include <algorithm>
#include "forwardchecking.h"


ForwardChecking::ForwardChecking(int hoteles, int pois, int dias, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist){
  this->H = hoteles;
  this->N = pois;
  this->D = dias;
  this->S = scores;
  this->t = dist;
  this->T = maxdist;
  
  this->InitVariables(); 
}

void ForwardChecking::InitVariables(){
  this->X.resize(this->D + 1);
  this->Dom_iteracion_X.resize(this->D + 1);
  this->Dom_X.resize(this->H + this->N + 1);

  for(int l = 0; l <= this->H + this->N; l++){
    this->Dom_X[l] = l;
  }
  
  this->CheckForward(1,0);
}

vector<int> ForwardChecking::Hoteles(){
  vector<int> hoteles;
  for(int l = 0; l <= this->H; l++)
    hoteles.push_back(l);
  
  return hoteles;
}

vector<int> ForwardChecking::POIs(){
  vector<int> pois;
  for(int l = this->H + 1; l <= this->H + this->N; l ++)
    pois.push_back(l);
  
  return pois;
}

void ForwardChecking::MostrarInstancia(){
  cout << "Hay " << this->H << "+1 hoteles y " << this->N << " puntos de interés." << endl << endl ;
  
  cout << "Limites de los " << this->D << " trips " << endl;
  for(int d = 1; d <= this->D; d++){
     cout << this->T[d] << " ";
  }
  cout << endl << endl;
  
  cout << "Hoteles = {";
  vector<int> hoteles = this->Hoteles();
  for(int h = 0; h < hoteles.size(); h++){
    if(h>0)
      cout << ", ";
    cout << hoteles[h];
  }
  cout << "}" << endl;
  
  cout << "POIs = {";
  vector<int> pois = this->POIs();
  for(int p = 0; p < pois.size(); p++){
    if(p>0)
      cout << ", ";
    cout << pois[p];
  }
  cout << "}" << endl;
  
  for(int i = 0; i <= this->H + this->N; i++){
    cout << endl << "Lugar " << i << ":" << endl << "Score: " << this->S[i] << endl;
    cout << "Distancias:" << endl;
    for(int j = 0; j <= this->H + this->N; j++){
      cout << j << ": " << t[i][j] << ", ";
    }
  }
  cout << endl;
}

void ForwardChecking::MostrarDominio(int d, int i){
  cout << "Dom_X(" << d << ", " << i << ") = {";
  for(int l = 0; l < this->Dom_iteracion_X[d][i].size(); l++){
    if(l>0)
      cout << ", ";
    cout << this->Dom_iteracion_X[d][i][l];
  }
  cout << "}" << endl << endl;
}

void ForwardChecking::CrearDominio(int d, int i){
  if(this->Dom_iteracion_X[d].size() < i+1)
    this->Dom_iteracion_X[d].resize(i+1);
  
  this->Dom_iteracion_X[d][i].resize(this->Dom_X.size());
  
  for(int l = 0; l < this->Dom_X.size(); l++)
    this->Dom_iteracion_X[d][i][l] = this->Dom_X[l];  
}

void ForwardChecking::FiltrarDominio(int d, int i){
  vector<int> pois = this->POIs();
  vector<int> hoteles = this->Hoteles();
  
  // El punto de partida el día 1 es el hotel 0 (l = 0)
  if(i == 0 && d == 1){
    for(int l = 1; l <= this->H + this->N; l++)
    this->EliminarDominio(d,i,l);
  }
  // El punto de partida de todo día es un hotel
  else if(i == 0){
    for(int p = 0; p < pois.size(); p++)
      this->EliminarDominio(d,i,pois[p]);
  }
  
 
}

void ForwardChecking::EliminarDominio(int d, int i, int l){
  this->Dom_iteracion_X[d][i].erase(remove(this->Dom_iteracion_X[d][i].begin(), this->Dom_iteracion_X[d][i].end(), l), this->Dom_iteracion_X[d][i].end());
}

bool ForwardChecking::EsPOI(int l){
  vector<int> pois = this->POIs();
  return find(pois.begin(), pois.end(), l) != pois.end();
}

bool ForwardChecking::Instanciar(int d, int i){   
  if(this->Dom_iteracion_X[d].empty())
    return false;
  
  this->MostrarDominio(d,i);
  cout << "Instanciando d=" << d << ", i=" << i << endl;

  this->X[d].resize(i+1);
  this->X[d][i] = this->Dom_iteracion_X[d][i].front();
  this->Dom_iteracion_X[d][i].erase(this->Dom_iteracion_X[d][i].begin());
  
  cout << "X[" << d << "][" << i << "] = " <<  this->X[d][i] << endl << endl;
  
  return true;
}
  
  
int ForwardChecking::CheckForward(int d, int i){
  vector<int> pois = this->POIs();
  vector<int> hoteles = this->Hoteles();
  
  // Clonar Dominio Base para la iteración
  this->CrearDominio(d,i);
  
  // Filtrar Dominio segun restricciones
  // El punto de partida el día 1 es el hotel 0 (l = 0)
  if(i == 0 && d == 1){
    for(int l = 1; l <= this->H + this->N; l++)
    this->EliminarDominio(d,i,l);
  }
  // El punto de partida de todo día es un hotel
  else if(i == 0){
    for(int p = 0; p < pois.size(); p++)
      this->EliminarDominio(d,i,pois[p]);
  }
  
  return i;
}

int ForwardChecking::CBJ(int d, int i){

}
