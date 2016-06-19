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
  
  bool puedoInstanciar = true;

  helper.LeerInstancia(path, H, N, D, S, t, T);  
  ForwardChecking forwardchecking(H, N, D, S, t, T);
   
  int primeraVariable = H + 1;
  int ultimaVariable = H + N;
  int i = primeraVariable;
  while(true){
    //cout << i << endl;   
    puedoInstanciar = forwardchecking.Instanciar(i);
    
    if(i == ultimaVariable && puedoInstanciar){
      cout << "Solución candidata ";
      forwardchecking.Instancia_u();
    }else if(puedoInstanciar){
      // Revisar dominios de variables futuras y avanzar
      i = forwardchecking.CheckForward(i);
    }else{
      //volver a variable i
      i = forwardchecking.CBJ(i);
    }
    
    if(i == primeraVariable && forwardchecking.DominioVacio(primeraVariable))
      break;
  }
  
  return 0;
}