using namespace std;
#include "forwardchecking.h"

void ForwardChecking::Dominio(int i, int j, int k){
  cout << "Dom_X(" << i<< "->" << j << ", " << k << ") = {";
  for(unsigned int l = 0; l < this->Dom_X[i][j][k].size(); l++){
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
  vector<int> ruta = this->Ord_u[this->iterador_u];
  
// Origen en el día k = 1 solo puede ser hotel 0
  for(int i = 1; i <= this->H; i++){
    for(int j = 0; j <= this->H + this->N; j++){
      this->DominioEliminar(i,j,1,1);
    }
  }

// Destino en el día k = D solo puede ser el hotel 1
  for(int i = 0; i <= this->H + this->N; i++){
    for(int j = 0; j <= this->H; j++){
      if(j!=1)
        this->DominioEliminar(i,j,this->D,1);
    }
  }
  
// El destino en el día k = 1 desde el hotel 0 solo puede ser un hotel, o el primer elemento de la ruta
  for(int j = H+1; j <= this->H + this->N; j++){
    if(j!=ruta[0])
      this->DominioEliminar(0,j,1,1);
  }
  
// Todos los días
  for(int k = 1; k <= this->D; k++){
// El primer elemento de la ruta solo puede ser visitado despues de hoteles
    for(int i = H+1; i <= this->H + this->N; i++){
      this->DominioEliminar(i,ruta[0],k,1);
    }
    
// El origen para los elementos de la ruta, es el elemento anterior o un hotel
    for(unsigned int r = 1; r < ruta.size(); r++){
      for(int i = H+1; i <= this->H + this->N; i++){
        if(i!=ruta[r-1])
          this->DominioEliminar(i,ruta[r],k,1);
      }
    }
// Para POIs, no pueden ser visitados por ellos mismos      
    for(int i = H+1; i <= this->H + this->N; i++){
      this->DominioEliminar(i,i,k,1);
    }
    
  }
  

  
}
