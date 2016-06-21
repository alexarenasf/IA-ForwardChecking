using namespace std;
#include "forwardchecking.h"

void ForwardChecking::ConflictoAgregar_ijk(int iijjkk, int ijk){
  this->Conf_X[iijjkk].push_back(ijk);
  
  int i,j,k;
  i = this->Ord_ijk[ijk][0];
  j = this->Ord_ijk[ijk][1];
  k = this->Ord_ijk[ijk][2];
  
  stringstream ss;
  ss << "X[" << i << "][" << j << "][" << k << "] = " << this->X[i][j][k];
  
  this->Conf_X_detalle[iijjkk][ijk] = ss.str();
  
  sort(this->Conf_X[iijjkk].begin(), this->Conf_X[iijjkk].end());
  reverse(this->Conf_X[iijjkk].begin(), this->Conf_X[iijjkk].end());
}

void ForwardChecking::ConflictoComer_ijk(int ijk, int iijjkk){
  for(unsigned int j = 0; j <= this->Conf_X[iijjkk].size();j++){
    this->ConflictoAgregar(this->Conf_X[iijjkk][j],ijk);
  }
}
