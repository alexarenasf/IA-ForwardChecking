using namespace std;
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
  this->X.resize(this->H + this->N + 1);
  this->Dom_X.resize(this->H + this->N + 1);
  
  for(int i = 0; i <= this->H + this->N; i++){
    this->X[i].resize(this->H + this->N + 1);
    this->Dom_X[i].resize(this->H + this->N + 1);
    
    for(int j = 0; j <= this->H + this->N; j++){
      this->X[i][j].resize(this->D + 1);
      this->Dom_X[i][j].resize(this->D + 1);
      
      for(int k = 1; k <= this->D; k++){
        this->Dom_X[i][j][k].resize(2);
        
        this->Dom_X[i][j][k][0] = 1;
        this->Dom_X[i][j][k][1] = 0;
      }
    }
  }
  
  this->u.resize(this->H + this->N + 1);
  this->Dom_u.resize(this->H + this->N + 1);
  this->ImDom_u.resize(this->H + this->N + 1);
   
  for(int i = this->H+1; i <= this->H + this->N; i++){
    this->ImDom_u[i].resize(this->H + this->N + 1);
    
    for(int n = 1; n <= this->N; n++){
      this->Dom_u[i].push_back(n);
    }
  } 
  
  this->Conf_u.resize(this->H + this->N + 1);
  
  
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

void ForwardChecking::MostrarDia(int k){
  for(int j = 0; j<= this->H + this->N; j++){
    cout << "-----";
  }
  cout << "-" << endl;
  cout << "| i\\j" << " | ";
  for(int j = 0; j<= this->H + this->N; j++){
    cout << j << " | ";
  }
  cout << endl;
  for(int j = 0; j<= this->H + this->N; j++){
    cout << "-----";
  }
  cout << "-" << endl;
  
  for(int i = 0; i<= this->H + this->N; i++){
    cout << "|  " << i << "  | ";
    for(int j = 0; j<= this->H + this->N; j++){
      cout << this->X[i][j][k] << " | ";
    }
    cout << endl;
    for(int j = 0; j<= this->H + this->N; j++){
      cout << "-----";
    }
    cout << "-" << endl;
  }
}

