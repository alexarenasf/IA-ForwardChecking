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
  
  bool consistente;
  int iteracion = 0;
  int dia = 1;

  helper.LeerInstancia(path, H, N, D, S, t, T);  
  ForwardChecking forwardchecking(H, N, D, S, t, T);
  //forwardchecking.MostrarInstancia();
  
  
  consistente = true;
  iteracion = 0;
  
  for(int i = 0; i < 5; i++){
    cout << "Iteración " << iteracion << endl << "============" << endl;
    consistente = forwardchecking.Instanciar(dia, iteracion);
    if(consistente){
      iteracion = forwardchecking.CheckForward(dia, iteracion + 1);
    }else{
      iteracion = forwardchecking.CBJ(dia, iteracion);
    }
  }
  
  
  // for(int i = 0; i <= H + N + 1; i++){
    // for(int j = 0; j <= H + N + 1; j++){
      // for(int k = 0; k < D; k++){
        // forwardchecking.Instanciar(i,j,k);
      // }
    // }
  // }
      
  
  
  
  return 0;
}