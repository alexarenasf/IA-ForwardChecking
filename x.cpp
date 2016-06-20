using namespace std;
#include "forwardchecking.h"

void ForwardChecking::IteradorCrear(){
  vector<int> ijk;
  ijk.resize(3);
    
  for(int k = 1; k <= this->D; k++){
    for(int i = 0; i <= this->H; i++){
      for(int j = 0; j <= this->H + this->N; j++){
        ijk[0]=i;
        ijk[1]=j;
        ijk[2]=k;
        
        this->Ord_ijk.push_back(ijk);
      }
    }
    
    for(int i = 0; i < this->N; i++){
      for(int j = 0; j <= this->H + this->N; j++){
        ijk[0]=this->Ord_u[this->iterador_u][i];
        ijk[1]=j;
        ijk[2]=k;
        
        this->Ord_ijk.push_back(ijk);
      }
    }
  } 
  
  this->iterador_ijk = 0;
}

void ForwardChecking::IteradorSet_ijk(int &i, int &j, int &k){
  i = this->Ord_ijk[iterador_ijk][0];
  j = this->Ord_ijk[iterador_ijk][1];
  k = this->Ord_ijk[iterador_ijk][2];
}

bool ForwardChecking::IteradorPrimero(){
  int i = this->Ord_ijk[iterador_ijk][0];
  int j = this->Ord_ijk[iterador_ijk][1];
  int k = this->Ord_ijk[iterador_ijk][2];
  
  return ((i == this->Ord_ijk[0][0]) && (j == this->Ord_ijk[0][1]) && (k == this->Ord_ijk[0][2]));
}

bool ForwardChecking::IteradorUltimo(){
  int i = this->Ord_ijk[iterador_ijk][0];
  int j = this->Ord_ijk[iterador_ijk][1];
  int k = this->Ord_ijk[iterador_ijk][2];
  
  return ((i == this->Ord_ijk[this->Ord_ijk.size()-1][0]) && (j == this->Ord_ijk[this->Ord_ijk.size()-1][1]) && (k == this->Ord_ijk[this->Ord_ijk.size()-1][2]));
}


void ForwardChecking::IteradorAvanzar(int &i, int &j, int &k){
  if(this->iterador_ijk < this->Ord_ijk.size()-1)
    this->iterador_ijk++;
  this->IteradorSet_ijk(i,j,k);
}

void ForwardChecking::IteradorRetroceder(int &i, int &j, int &k){
  if(this->iterador_ijk > 0)
    this->iterador_ijk--;
  this->IteradorSet_ijk(i,j,k);
}

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
  bool esPoi = false;
  if(this->H < j)
    esPoi = true;
  bool esHotel = !esPoi;

//for(int kk = k; kk <= this->D + 1; kk++){
//for(int ii = i; ii <= this->H + this->N; ii++){
//for(int jj = j + 1; jj <= this->H + this->N; jj++){
          
//~ // Cada POI puede ser visitado a lo más una vez
  //~ if(esPoi && valorActual == 1){
    //~ //cout << "(" << i << "," << j << ") es POI" << endl;   
    //~ for(int kk = k; kk <= this->D; kk++){
      //~ for(int ii = 0; ii <= this->H + this->N; ii++){
        //~ if((kk == k && ii > i) || (kk > k)){
          //~ //cout << "Eliminar 1 de (" << ii << "," << j << "," << kk << ")" << endl;          
          //~ this->DominioEliminar(ii,j,kk,1);
        //~ }
      //~ }
    //~ }
  //~ }
//~ 
//~ // El trip termina en un hotel cualquiera, por lo tanto ya no se pueden visitar trips
  //~ if(esHotel){
    //~ for(int ii = i ; ii <= this->H + this->N; ii++){
      //~ for(int jj = j + 1; jj <= this->H + this->N; jj++){
        //~ this->DominioEliminar(ii,jj,k,1);
      //~ }
    //~ }
  //~ }
        

  this->IteradorAvanzar(i,j,k);

        

}

void ForwardChecking::CBJ(int &i, int &j, int &k){

}
