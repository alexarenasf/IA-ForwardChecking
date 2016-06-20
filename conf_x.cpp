using namespace std;
#include "forwardchecking.h"

void ForwardChecking::ConflictoAgregar_ijk(int iijjkk, int ijk){
  this->Conf_X[iijjkk].push_back(ijk);
  
  sort(this->Conf_X[iijjkk].begin(), this->Conf_X[iijjkk].end());
  reverse(this->Conf_X[iijjkk].begin(), this->Conf_X[iijjkk].end());
}

void ForwardChecking::ConflictoComer_ijk(int ijk, int iijjkk){
  for(unsigned int j = 0; j <= this->Conf_X[iijjkk].size();j++){
    this->ConflictoAgregar(this->Conf_X[iijjkk][j],ijk);
  }
}
