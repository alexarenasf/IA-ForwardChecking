using namespace std;
#include "forwardchecking.h"

void ForwardChecking::Instancia_u(){
  cout << "u = [ ";
  for(int i = 0; i <= this->H; i++)
    cout << "- | ";
  
  for(int i = this->H + 1; i <= this->H + this->N; i++){
    if(i>this->H + 1)
      cout << " | ";
    cout << this->u[i];
  }
  cout << " ]" << endl;
}

string ForwardChecking::Ruta_u(){
  vector<int> ruta;
  stringstream ss;
  
  ruta.resize(this->u.size()-(this->H+1));
  for(int i = this->H+1; i <= this->H + this->N; i++){
    ruta[this->u[i]-1] = i;
  }
  
  for(unsigned int i = 0; i < ruta.size(); i++){
    if(i>0){
      cout << "->";
      ss << " ";
    }
    cout << ruta[i];
    ss << ruta[i];
  }
  cout << endl;
  
  return ss.str();
}

void ForwardChecking::SiguienteRuta(){
  this->iterador_u++;
}

bool ForwardChecking::NoHayMasRutas(){
  return (this->iterador_u==this->Ord_u.size());
}

bool ForwardChecking::Instanciar(int i){   
  if(this->DominioVacio(i))
    return false;
  
  //Preimagen para otras variables
  for(int ii = this->H + 1; ii <= this->H + this->N; ii++){
    if(ii != i){
      this->ImagenDominioCrear(i,ii);
    }
  }
  
  this->u[i] = this->DominioPop(i);
   
  //Postimagenes para variable instanciada
  this->ImagenDominioCrear(i,i);
  
  return true;
}

int ForwardChecking::CheckForward(int i){   
// Filtrar Dominio segun restricciones
  int valorActual = this->u[i];
  
// Para todo ii > i, respetar secuencia, no repetir valores
  for(int ii = i + 1; ii <= this->H + this->N; ii++){

// Variable i le borra del dominio a la variable ii el valor valorActual
    this->DominioEliminar(ii,valorActual);
// La variable futura ii ahora tiene conflictos con ii
    this->ConflictoAgregar(ii,i);
        
//Si el dominio de la variable ii > i queda vacío, copiar el conjunto conflicto de ii en i, despues probar con otro valor par i
    if(this->DominioVacio(ii)){
      this->ConflictoComer(i,ii);
      return i;
    }
  }
  return i+1;
}

int ForwardChecking::CBJ(int i){
// Por defecto, el salto es cronológico hacia atrás
  int saltarA = i-1;

// A menos que el conjunto conflicto de i no esté vacío
  if(!this->Conf_u[i].empty()){
    saltarA = this->Conf_u[i][0];
  }
  
//Restaurar Dominios al punto saltarA
  this->ImagenDominioRestaurar(saltarA);
  return saltarA;
}
