using namespace std;
#include "forwardchecking.h"


ForwardChecking::ForwardChecking(int hotels, int pois, int days, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist){
  this->H = hotels;
  this->N = pois;
  this->D = days;
  this->S = scores;
  this->t = dist;
  this->T = maxdist;
  
  this->InitVariables(); 
}

void ForwardChecking::InitVariables(){
  this->X.resize(this->H + this->N + 1);
  for(int i = 0; i <= this->H + this->N; i++){
    this->X[i].resize(this->H + this->N + 1);
    for(int j = 0; j <= this->H + this->N; j++){
      this->X[i][j].resize(this->D);
      for(int k = 0; k <= this->H + this->N; k++){
        this->X[i][j][k] = false;
      }
    }
  }
}

void ForwardChecking::MostrarInstancia(){
  cout << "Hay " << this->H << "+1 hoteles y " << this->N << " puntos de interés." << endl ;
  
  cout << "Limites de los " << this->D << " trips " << endl;
  for(int d = 0; d < this->D; d++){
     cout << this->T[d] << " ";
  }
  cout << endl;
  
  for(int i = 0; i <= this->H + this->N; i++){
    cout << endl << i << ":" << endl << "Score: " << this->S[i] << endl;
    cout << "Distancias:" << endl;
    for(int j = 0; j <= this->H + this->N; j++){
      cout << j << ": " << t[i][j] << ", ";
    }
  }
}
  
