using namespace std;
#include "helper.h"
#include "forwardchecking.h"

int main(){
  string path = "./instances/SET0/5-20-1-2.ophs";
  Helper helper;

  int H;
  int N;
  int D;
  vector<int> S;
  vector<vector<double> > t;
  vector<double> T;
  
  helper.LeerInstancia(path, H, N, D, S, t, T);  
  ForwardChecking forwardchecking(H, N, D, S, t, T);
  
  int i,j,k;
  bool puedoInstanciar;
  
// Variable u[i]
  puedoInstanciar = true;   
  int primeraVariable = H + 1;
  int ultimaVariable = H + N;
  i = primeraVariable;
  while(true){
    puedoInstanciar = forwardchecking.Instanciar(i);
    
    if(i == ultimaVariable && puedoInstanciar){
      cout << "Solución candidata ";
      forwardchecking.Instancia_u();
    }else if(puedoInstanciar){
// Revisar dominios de variables futuras y avanzar a la variable i
      i = forwardchecking.CheckForward(i);
    }else{
//volver a variable i
      i = forwardchecking.CBJ(i);
    }
    
    if(i == primeraVariable && forwardchecking.DominioVacio(i))
      break;
  }
  
// Variable X[i][j][k]  
  puedoInstanciar = true;   
  int primeraVariable_i, primeraVariable_j, primeraVariable_k;
  int ultimaVariable_i, ultimaVariable_j, ultimaVariable_k;
  
  primeraVariable_i = 0; // Origen: Hotel i = 0
  primeraVariable_j = 0; // Destino: Hotel j = 1
  primeraVariable_k = 1; // Día k = 1
  
  ultimaVariable_i = H + N + 1; // Origen: POI i = H+N+1
  ultimaVariable_j = H + N + 1; // Destino: POI j = H+N+1
  ultimaVariable_k = D; // Día k = D
  
  i = primeraVariable_i;
  j = primeraVariable_j;
  k = primeraVariable_k;
  
  forwardchecking.DominioEliminar(0,0,1,1);
  
  while(true){
    puedoInstanciar = forwardchecking.Instanciar(i,j,k);
    
    if((i == ultimaVariable_i && j == ultimaVariable_j && k == ultimaVariable_k) && puedoInstanciar){
      cout << "Solución candidata ";
    }else if(puedoInstanciar){
// Revisar dominios de variables futuras y avanzar a la variable i
      forwardchecking.CheckForward(i,j,k);
    }else{
//volver a variable i
      forwardchecking.CBJ(i,j,k);
    }
    
    if((i == primeraVariable_i && j == primeraVariable_j && k == primeraVariable_k) && forwardchecking.DominioVacio(i,j,k))
      break;
    
    if(k > ultimaVariable_k)
      break;
  }
  
  
  return 0;
}