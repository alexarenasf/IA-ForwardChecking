using namespace std;
#include "forwardchecking.h"

void ForwardChecking::Dominio(int i, int j, int k){
  cout << "Dom_X(" << i<< "->" << j << ", " << k << ") = {";
  for(int l = 0; l < this->Dom_X[i][j][k].size(); l++){
    if(l>0)
      cout << ", ";
    cout << this->Dom_X[i][j][k][l];
  }
  cout << "}" << endl;
}

bool ForwardChecking::DominioVacio(int i, int j, int k){
  return this->Dom_X[i][j][k].empty();
}

void ForwardChecking::DominioEliminar(int i, int j, int k, int l){
  this->Dom_X[i][j][k].erase(remove(this->Dom_X[i][j][k].begin(), this->Dom_X[i][j][k].end(), l), this->Dom_X[i][j][k].end());
}

bool ForwardChecking::DominioContiene(int i, int j, int k, int l){
  return find(Dom_X[i][j][k].begin(), Dom_X[i][j][k].end(), l) != Dom_X[i][j][k].end();
}

int ForwardChecking::DominioPop(int i, int j, int k){
  int primero = this->Dom_X[i][j][k].front();
  this->Dom_X[i][j][k].erase(this->Dom_X[i][j][k].begin());
  return primero;
}

void ForwardChecking::DominioFiltrar_X(){
// Origen en el día k = 1 solo puede ser hotel 0
  for(int i = 1; i <= this->H; i++){
    for(int j = 0; j <= this->H + this->N + 1; j++){
      this->DominioEliminar(i,j,1,1);
    }
  }
}