using namespace std;
#include "forwardchecking.h"

void ForwardChecking::ConflictoAgregar(int ii, int i){
  this->Conf_u[ii].push_back(i);
  
  sort(this->Conf_u[ii].begin(), this->Conf_u[ii].end());
  reverse(this->Conf_u[ii].begin(), this->Conf_u[ii].end());
}

void ForwardChecking::ConflictoComer(int i, int ii){
  for(unsigned int j = 0; j <= this->Conf_u[ii].size();j++){
    this->ConflictoAgregar(this->Conf_u[ii][j],i);
  }
}
