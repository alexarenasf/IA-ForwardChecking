using namespace std;
#include "forwardchecking.h"

void ForwardChecking::Instancia_u(){
  cout << "u = [ ";
  for(int i = this->H + 1; i <= this->H + this->N; i++){
    if(i>this->H + 1)
      cout << " | ";
    cout << this->u[i];
  }
  cout << " ]" << endl;
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
  //cout << "u[" << i << "]= " <<  this->u[i] << endl;
   
  //Postimagenes para variable instanciada
  this->ImagenDominioCrear(i,i);
  
  return true;
}

int ForwardChecking::CheckForward(int i){   
// Filtrar Dominio segun restricciones
  int valorActual = this->u[i];
  
// Para todo ii > i, respetar secuencia, no repetir valores
  for(int ii = i + 1; ii <= this->H + this->N; ii++){
    //cout << "FC de " << i << " sobre " << ii << endl;
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