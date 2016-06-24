using namespace std;
#include "forwardchecking.h"

int main(int argc, char **argv){
  cout << "Algoritmo Forward Checking + Conflict-directed Back Jumping para el OPHS" << endl;
  cout << "Alex Arenas F." << endl << endl;
  
  if(argc<3){
    cout << "Faltan parámetros." << endl << endl;
    cout << "Para ejecutar escribir" << endl;
    cout << "> make INSTANCE={instancia}" << endl << endl;
    cout << "Debe existir el archivo ./instances/SET0/{instancia}.ophs" << endl << endl;
    cout << "Para más información, lea el archivo Readme.md" << endl << endl;
    return 0;
  }
  
  bool rehacer_u = false;
  stringstream p;
  string path = "";
  Helper helper;
  string instancia = "";
  stringstream rutas_path;
  
  p << "./instances/SET0/";
  
  for(int i = 1; i < argc; i++){    
    if(strcmp(argv[i],"-instance")==0){
      if(argc>=3){
        instancia = argv[i+1];
        p << argv[i+1];
        p << ".ophs";
        path = p.str();
      }
      i++;
    }else if(strcmp(argv[i],"-make-routes")==0){
      rehacer_u = true;
    }
  }
  
  if(instancia.empty()){
    cout << "No se ha especificado una instancia." << endl << endl;
    return 0;
  }
    
  if(!helper.ArchivoExiste(path)){
    cout << "No Existe la instancia " << path << endl << endl;
    return 0;
  }

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
  
  rutas_path << "./tmp/";
  rutas_path << instancia;
  rutas_path << ".routes";
  
  helper.TiempoIniciar();
  
  // Protección contra sobreescritura de rutas
  if(rehacer_u){
    string respuesta;
    
    if(helper.ArchivoExiste(rutas_path.str())){
      do{
        cout << "Ya existe un archivo de rutas generado, desea sobreescribirlo? [S/n] ";
        getline(cin, respuesta);
      }while(respuesta.compare("S")!=0 && respuesta.compare("n")!=0);
      
      if(respuesta.compare("n")==0)
        rehacer_u = false;
    }
    
  }else{
    // Si no existe el archivo de rutas, hay que hacerlo
    if(!helper.ArchivoExiste(rutas_path.str())){
      rehacer_u = true;
    }
    
  }
  
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
  //Solución
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
    //Condiciones iniciales
    forwardchecking.DominioFiltrar_X();

    bool checkearDominio = false;
    puedoInstanciar = true;     
    string sn;
    
    while(true){        
      forwardchecking.IteradorSet_ijk(i,j,k);
        
      puedoInstanciar = forwardchecking.Instanciar(i,j,k);
      
      if(forwardchecking.IteradorUltimo() && puedoInstanciar){
  // Solución
        if(forwardchecking.Instancia_X(helper)){
          helper.TiempoGuardar("Tour Solución encontrado","X");
        }
                
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
  // Fin del recorrido, se retornó a la raiz y no quedan más valores que instanciar
        break;
        
      }
      
    }
    helper.TiempoGuardar("Terminando la ruta","X");
    forwardchecking.SiguienteRuta();
  }
  helper.TiempoGuardar("Terminada la busqueda","X");
  
  return 0;
}
