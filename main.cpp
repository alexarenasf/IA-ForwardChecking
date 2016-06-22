using namespace std;
#include "forwardchecking.h"

int main(){
  string path = "./instances/SET0/32-65-1-2.ophs";
  Helper helper;

  int H;
  int N;
  int D;
  vector<int> S;
  vector<vector<double> > t;
  vector<double> T;
  
  bool rehacer_u = true;
    
  helper.LeerInstancia(path, H, N, D, S, t, T);    
  ForwardChecking forwardchecking(H, N, D, S, t, T);
  
  int i,j,k;
  bool puedoInstanciar;
  
  helper.TiempoIniciar();
  
// Variable u[i]
if(rehacer_u){
  helper.ReiniciarArchivos();
  
  puedoInstanciar = true;   
  int primeraVariable = H + 1;
  int ultimaVariable = H + N;
  i = primeraVariable;
  
  helper.TiempoGuardar("Iniciando creación de rutas","u");
  
  while(true){
    puedoInstanciar = forwardchecking.Instanciar(i);
    
    if(i == ultimaVariable && puedoInstanciar){
      //forwardchecking.Instancia_u();
      //cout << forwardchecking.Ruta_u();
      helper.EscribirRuta(forwardchecking.Ruta_u());
      helper.TiempoGuardar("Ruta creada","u");
    }else if(puedoInstanciar){
// Revisar dominios de variables futuras y avanzar a la variable i
      i = forwardchecking.CheckForward(i);
      helper.TiempoGuardar("Checkeando Dominios futuros","u_FC");
    }else{
//volver a variable i
      i = forwardchecking.CBJ(i);
      helper.TiempoGuardar("Retorno Inteligente","u_CBJ");
    }
    
    if(i == primeraVariable && forwardchecking.DominioVacio(i))
      break;
  }
}

  helper.TiempoGuardar("Creación de rutas terminada","u");

  vector<vector<int> > rutas;
  helper.LeerRutas(rutas,N);
  forwardchecking.SetRutas(rutas);

  helper.TiempoGuardar("Iniciando la busqueda de Tours factibles","X");
  
// Variable X[i][j][k]  
  while(!forwardchecking.NoHayMasRutas()){
    helper.TiempoGuardar("Usando nueva ruta","X");
    forwardchecking.DominioReiniciar_ijk();

    forwardchecking.IteradorCrear(); 
    
    //~ forwardchecking.DominioEliminar(0,0,1,1);
    //~ forwardchecking.DominioEliminar(0,1,1,1);
    //~ forwardchecking.DominioEliminar(0,2,1,1);
    forwardchecking.DominioFiltrar_X();
    
    //~ forwardchecking.Dominio_ijk();
        //~ cin.get();
    bool checkearDominio = false;
    puedoInstanciar = true;     
    string sn;
    
    while(true){        
      forwardchecking.IteradorSet_ijk(i,j,k);
        
      puedoInstanciar = forwardchecking.Instanciar(i,j,k);
      
      if(forwardchecking.IteradorUltimo() && puedoInstanciar){
        //cout << "Solución candidata " << endl;
        if(forwardchecking.Instancia_X(helper)){
          helper.TiempoGuardar("Tour Solución encontrado","X");
        }
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
        helper.TiempoGuardar("Checkeando Dominios futuros","X_FC");
        if(checkearDominio){
          cout << "FC" << endl;
          forwardchecking.Dominio_ijk();
          getline(cin, sn);
        }
      }else{
  //volver a variable i
        forwardchecking.CBJ(i,j,k);
        helper.TiempoGuardar("Retorno Inteligente","X_CBJ");
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
    helper.TiempoGuardar("Terminando la ruta","X");
    forwardchecking.SiguienteRuta();
  }
  helper.TiempoGuardar("Terminada la busqueda","X");
  
  return 0;
}
