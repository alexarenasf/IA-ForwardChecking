using namespace std;
#include "forwardchecking.h"

bool ForwardChecking::Instanciar(int i, int j, int k){   
  //cout << i << "," << j << "," << k << endl;
  if(this->DominioVacio(i,j,k))
    return false;
  this->X[i][j][k] = this->DominioPop(i,j,k);
  //cout << "X[" << i << "][" << j << "][" << k << "]= " <<  this->X[i][j][k] << endl;
  return true;
}

void ForwardChecking::CheckForward(int &i, int &j, int &k){
  vector<int> pois = this->POIs();
  vector<int> hoteles = this->Hoteles();
    
// Filtrar Dominio segun restricciones
  int valorActual = this->X[i][j][k];
  int noValorActual = 1;
  if(valorActual==1)
    noValorActual = 0;
  bool esPoi = false;
  if(this->H < j)
    esPoi = true;
  bool esHotel = !esPoi;

//for(int kk = k; kk <= this->D + 1; kk++){
//for(int ii = i; ii <= this->H + this->N; ii++){
//for(int jj = j + 1; jj <= this->H + this->N; jj++){
  
// Viaje se inicia en el hotel i = 0, cualquiera sea el destino labs  
  if(i == 0 && k == 1 && valorActual == 1){
    for(int ii = i + 1; ii <= this->H + this->N; ii++){
      this->DominioEliminar(ii,j,k,1);
    }
  }
          
// Viaje termina en el hotel i = 1, cualquiera sea el origen
        
        
// Cada POI puede ser visitado a lo más una vez
  if(esPoi && valorActual == 1){
    //cout << "(" << i << "," << j << ") es POI" << endl;   
    for(int kk = k; kk <= this->D; kk++){
      for(int ii = 0; ii <= this->H + this->N; ii++){
        if((kk == k && ii > i) || (kk > k)){
          //cout << "Eliminar 1 de (" << ii << "," << j << "," << kk << ")" << endl;          
          this->DominioEliminar(ii,j,kk,1);
        }
      }
    }
  }

// El trip termina en un hotel cualquiera, por lo tanto ya no se pueden visitar trips
  if(esHotel){
    for(int ii = i ; ii <= this->H + this->N; ii++){
      for(int jj = j + 1; jj <= this->H + this->N; jj++){
        this->DominioEliminar(ii,jj,k,1);
      }
    }
  }
        

  i++;
  if(i>this->H+this->H+1){
    i = 0;
    j++;
  }
  if(j>this->H+this->H+1){
    j = 0;
    this->MostrarDia(k);
    k++;
  }
        

}

void ForwardChecking::CBJ(int &i, int &j, int &k){

}