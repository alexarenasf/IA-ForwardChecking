using namespace std;
#include "helper.h"
#include "forwardchecking.h"

int main(){
  string path = "./instances/SET0/6-20-1-2.ophs";
  Helper helper;

  int H;
  int N;
  int D;
  vector<int> S;
  vector<vector<double> > t;
  vector<double> T;
  
  bool rehacer_u = false;
  
  if(rehacer_u)
    helper.ReiniciarArchivos();
  
  helper.LeerInstancia(path, H, N, D, S, t, T);    
  ForwardChecking forwardchecking(H, N, D, S, t, T);
  
  int i,j,k;
  bool puedoInstanciar;
  
// Variable u[i]
if(rehacer_u){
  puedoInstanciar = true;   
  int primeraVariable = H + 1;
  int ultimaVariable = H + N;
  i = primeraVariable;
  while(true){
    puedoInstanciar = forwardchecking.Instanciar(i);
    
    if(i == ultimaVariable && puedoInstanciar){
      //forwardchecking.Instancia_u();
      //cout << forwardchecking.Ruta_u();
      helper.EscribirRuta(forwardchecking.Ruta_u());
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
}

  vector<vector<int> > rutas;
  helper.LeerRutas(rutas,N);
  forwardchecking.SetRutas(rutas);

  
// Variable X[i][j][k]  
  puedoInstanciar = true;     
  forwardchecking.IteradorCrear(); 
  
  //~ forwardchecking.DominioEliminar(0,0,1,1);
  //~ forwardchecking.DominioEliminar(0,1,1,1);
  //~ forwardchecking.DominioEliminar(0,2,1,1);
  forwardchecking.DominioFiltrar_X();
  
  //~ forwardchecking.Dominio_ijk();
      //~ cin.get();
  bool checkearDominio = false;
  string sn;
  
  while(true){    
    forwardchecking.IteradorSet_ijk(i,j,k);
      
    puedoInstanciar = forwardchecking.Instanciar(i,j,k);
    
    if(forwardchecking.IteradorUltimo() && puedoInstanciar){
      //cout << "Solución candidata " << endl;
      forwardchecking.Instancia_X();
      //~ for(int d = 1; d <= D; d++)
        //~ forwardchecking.MostrarDia(d);
      //~ cin.get();
      
      //~ getline(cin, sn);
      //~ if(sn == "s")
        //~ checkearDominio = true;
      //~ else
        //~ checkearDominio = false;
      
    }else if(puedoInstanciar){
// Revisar dominios de variables futuras y avanzar a la variable ijk
      forwardchecking.CheckForward(i,j,k);
      if(checkearDominio){
        cout << "FC" << endl;
        forwardchecking.Dominio_ijk();
        getline(cin, sn);
      }
    }else{
//volver a variable i
      forwardchecking.CBJ(i,j,k);
      if(checkearDominio){
        cout << "CBJ" << endl;
        forwardchecking.Dominio_ijk();
        getline(cin, sn);
      }
    }
    
    if(forwardchecking.IteradorPrimero() && forwardchecking.DominioVacio(i,j,k)){
      //forwardchecking.Dominio_ijk();
      break;
    }
    
  }
  
  
  return 0;
}
