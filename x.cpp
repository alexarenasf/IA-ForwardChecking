using namespace std;
#include "forwardchecking.h"

void ForwardChecking::IteradorCrear(){
  vector<int> ijk;
  ijk.resize(3);
    
  for(int k = 1; k <= this->D; k++){
    for(int i = 0; i <= this->H; i++){      
      for(int j = 0; j < this->N; j++){
        ijk[0]=i;
        ijk[1]=this->Ord_u[this->iterador_u][j];
        ijk[2]=k;
        
        //cout << "2:" << ijk[0] << ijk[1] << ijk[2] << endl;
        this->Ord_ijk.push_back(ijk);
      }
      for(int j = 0; j <= this->H; j++){
        ijk[0]=i;
        ijk[1]=j;
        ijk[2]=k;
        
        //cout << "1:" << ijk[0] << ijk[1] << ijk[2] << endl;
        this->Ord_ijk.push_back(ijk);
      }
    }
    
    for(int i = 0; i < this->N; i++){
      
      for(int j = 0; j < this->N; j++){
        ijk[0]=this->Ord_u[this->iterador_u][i];
        ijk[1]=this->Ord_u[this->iterador_u][j];
        ijk[2]=k;
        
        //cout << "4:" << ijk[0] << ijk[1] << ijk[2] << endl;
        this->Ord_ijk.push_back(ijk);
      }
      
      for(int j = 0; j <= this->H; j++){
        ijk[0]=this->Ord_u[this->iterador_u][i];
        ijk[1]=j;
        ijk[2]=k;
        
        //cout << "3:" << ijk[0] << ijk[1] << ijk[2] << endl;
        this->Ord_ijk.push_back(ijk);
      }
    }
  } 
  
  this->iterador_ijk = 0;
}

void ForwardChecking::IteradorSet_ijk(int &i, int &j, int &k){
  i = this->Ord_ijk[iterador_ijk][0];
  j = this->Ord_ijk[iterador_ijk][1];
  k = this->Ord_ijk[iterador_ijk][2];
}

bool ForwardChecking::IteradorPrimero(){
  int i = this->Ord_ijk[iterador_ijk][0];
  int j = this->Ord_ijk[iterador_ijk][1];
  int k = this->Ord_ijk[iterador_ijk][2];
  
  return ((i == this->Ord_ijk[0][0]) && (j == this->Ord_ijk[0][1]) && (k == this->Ord_ijk[0][2]));
}

bool ForwardChecking::IteradorUltimo(){
  int i = this->Ord_ijk[iterador_ijk][0];
  int j = this->Ord_ijk[iterador_ijk][1];
  int k = this->Ord_ijk[iterador_ijk][2];
  
  return ((i == this->Ord_ijk[this->Ord_ijk.size()-1][0]) && (j == this->Ord_ijk[this->Ord_ijk.size()-1][1]) && (k == this->Ord_ijk[this->Ord_ijk.size()-1][2]));
}


void ForwardChecking::IteradorAvanzar(int &i, int &j, int &k){
  if(this->iterador_ijk < this->Ord_ijk.size())
    this->iterador_ijk++;
  this->IteradorSet_ijk(i,j,k);
}

void ForwardChecking::IteradorRetroceder(int &i, int &j, int &k){
  if(this->iterador_ijk > 0)
    this->iterador_ijk--;
  this->IteradorSet_ijk(i,j,k);
}

void ForwardChecking::Instancia_X(){
  int i,j,k;
  
  //Verificar Restricciones
  int suma_destino_1 = 0;
  for(int i = 0; i <= this->H + this->N; i++){
    suma_destino_1 += this->X[i][1][this->D];
  }
  
  if(suma_destino_1 == 0)
    return;
  
  
  //Verificar Ruta instanciada
  vector<int> ruta;
  
  for(unsigned int ijk = 0; ijk < this->Ord_ijk.size(); ijk++){
    i = this->Ord_ijk[ijk][0];
    j = this->Ord_ijk[ijk][1];
    k = this->Ord_ijk[ijk][2];

    if(this->X[i][j][k] == 1 && j>this->H){
      ruta.push_back(j);
    }
  }
  
  for(unsigned int r = 0; r < ruta.size(); r++){
    if(ruta[r] != this->Ord_u[this->iterador_u][r])
      return;
  }
  
  cout << "0";
  for(unsigned int ijk = 0; ijk < this->Ord_ijk.size(); ijk++){
    i = this->Ord_ijk[ijk][0];
    j = this->Ord_ijk[ijk][1];
    k = this->Ord_ijk[ijk][2];

    if(this->X[i][j][k] == 1){
      cout << "->" << j;
    }
  }
  cout << endl;
}


void ForwardChecking::MostrarDia(int k){
  for(int j = 0; j<= this->H + this->N; j++){
    cout << "-----";
  }
  cout << "-" << endl;
  cout << "| i\\j" << " | ";
  for(int j = 0; j<= this->H + this->N; j++){
    cout << j << " | ";
  }
  cout << endl;
  for(int j = 0; j<= this->H + this->N; j++){
    cout << "-----";
  }
  cout << "-" << endl;
  
  for(int i = 0; i<= this->H + this->N; i++){
    cout << "|  " << i << "  | ";
    for(int j = 0; j<= this->H + this->N; j++){
      if(this->X[i][j][k] == 1)
        cout << this->X[i][j][k] << " | ";
      else
        cout << "- | ";
    }
    cout << endl;
    for(int j = 0; j<= this->H + this->N; j++){
      cout << "-----";
    }
    cout << "-" << endl;
  }
}

bool ForwardChecking::Instanciar(int i, int j, int k){   
  //cout << "(" << k << ")" << i << "->" << j << " [" << this->Dom_X[i][j][k].size() << "]" << endl;  
  if(this->DominioVacio(i,j,k))
    return false;
    
  //Preimagen para otras variables
  for(unsigned ijk = this->iterador_ijk + 1; ijk < this->Ord_ijk.size(); ijk++){
    if(ijk != this->iterador_ijk)
      this->ImagenDominioCrear_ijk(this->iterador_ijk,ijk);
  }
    
  this->X[i][j][k] = this->DominioPop(i,j,k);
  //cout << "X[" << i << "][" << j << "][" << k << "] = " <<  this->X[i][j][k] << endl;
  
  //if(this->X[i][j][k] == 1)
    //cout << "(" << k << ")" << i << "->" << j << " = " << this->X[i][j][k] << endl;
    
  //if(k == this->D && j == 1 && this->X[i][j][k] == 1){
    //this->Instancia_X();
  //}
  
  //Postimagenes para variable instanciada
  this->ImagenDominioCrear_ijk(this->iterador_ijk,this->iterador_ijk);
  
  return true;
}

void ForwardChecking::CheckForward(int &i, int &j, int &k){
  int ii,jj,kk;
// Filtrar Dominio segun restricciones
  int visitar_ijk = this->X[i][j][k];
  bool destinoEsPoi = false;
  if(this->H < j)
    destinoEsPoi = true;
  bool destinoEsHotel = !destinoEsPoi;
  bool dominioAniquilado = false;

  //cout << "X[" << i << j << k << "] = " << visitar_ijk << endl;
  
  vector <int> posteriores;
  
  if(destinoEsPoi){
// Buscar posteriores al poi actual en la ruta
    int r;

    for(unsigned int u = 0; u < this->Ord_u[this->iterador_u].size(); u++){
      if(this->Ord_u[this->iterador_u][u] == j){
        r = u+1;
      }
    }

    //cout << "Posteriores ";

    for(unsigned int u = r; u < this->Ord_u[this->iterador_u].size(); u++){
      posteriores.push_back(this->Ord_u[this->iterador_u][u]);
    }

      //cout << endl;
  }
  
  
  for(unsigned ijk = this->iterador_ijk + 1; ijk < this->Ord_ijk.size(); ijk++){
    ii = this->Ord_ijk[ijk][0];
    jj = this->Ord_ijk[ijk][1];
    kk = this->Ord_ijk[ijk][2];
      
   if(visitar_ijk == 1){       
      //~ if(k == kk)
      //~ cout << "- [" << ii << "][" << jj << "][" << kk  << "] " << ijk << ":[" << ijk << "]" << endl;
      
// Al visitar un destino, el resto de los destinos del mismo origen ya no pueden ser visitados    
      if(ii == i && kk == k){
        if(this->DominioEliminar(ii,jj,kk,1)){
          // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
          this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);
          
          //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
          if(this->DominioVacio(ii,jj,kk)){
            this->ConflictoComer_ijk(this->iterador_ijk,ijk);
            dominioAniquilado = true;
          }
        }
      }

// Cada POI puede ser visitado a lo más una vez
      if(destinoEsPoi){
//Destino del futuro jj es igual al destino actual j
//Origen del futuro ii es igual al origen actual i
        if((jj == j) || (kk > k && ii == j)){
          if(this->DominioEliminar(ii,jj,kk,1)){
            // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
            this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);   
            
            //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
            if(this->DominioVacio(ii,jj,kk)){
              this->ConflictoComer_ijk(this->iterador_ijk,ijk);
              dominioAniquilado = true;
            }
          }
        } 
      }
  
// El trip termina en un hotel cualquiera, por lo tanto ya no se pueden visitar más lugares en el día
      if(destinoEsHotel && kk == k){
        //cout << ii << jj << kk << " ";
        if(this->DominioEliminar(ii,jj,kk,1)){
          // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
          this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);
          
          //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
          if(this->DominioVacio(ii,jj,kk)){
            this->ConflictoComer_ijk(this->iterador_ijk,ijk);
            dominioAniquilado = true;
          }
        }
      }
// Para días menos el último (k < this->D)      
// Para todo día siguiente kk al día k actual (kk == k+1)
// Si el destinoEsHotel
// Solo puedo partir desde el origen ii == j (eliminar 1 de otros origenes)
// Si el origen ii es hotel (ii <= this->H+1)
      if(k<this->D && destinoEsHotel && ii != j && ii <= this->H && kk == k+1){
        //cout << "eliminando " << ii << jj << k+1 << endl;
        if(this->DominioEliminar(ii,jj,kk,1)){
          // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
          this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);
          
          //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
          if(this->DominioVacio(ii,jj,kk)){
            this->ConflictoComer_ijk(this->iterador_ijk,ijk);
            dominioAniquilado = true;
          }
        }
      }

// Si no se visita un POI
    }else{
      //~ if(destinoEsPoi && i == 2){
  //~ //No se pueden visitar ningun POI que siga despues de este poi en la ruta
        //~ for(unsigned int u = 0; u < posteriores.size(); u++){
          //~ if((jj == posteriores[u] || ii == posteriores[u]) && k == kk){
            //~ //cout << "Conflicto con " <<  ii << jj << kk << endl;
            //~ if(this->DominioEliminar(ii,jj,kk,1)){
              //~ // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
              //~ this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);   
              //~ 
              //~ //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
              //~ if(this->DominioVacio(ii,jj,kk)){
                //~ this->ConflictoComer_ijk(this->iterador_ijk,ijk);
                //~ dominioAniquilado = true;
              //~ } 
            //~ }
          //~ }
        //~ }
      //~ }
    }
  }
  
  //this->Dominio_ijk();
  //cin.get();
  
  //cout << endl << endl;
  //Si la instanciación actual produjo una aniquilación
  if(!dominioAniquilado)
    this->IteradorAvanzar(i,j,k);

        

}

void ForwardChecking::CBJ(int &i, int &j, int &k){
  int actual = this->iterador_ijk;
// A menos que el conjunto conflicto de i no esté vacío
  if(!this->Conf_X[this->iterador_ijk].empty()){
    this->iterador_ijk = this->Conf_X[this->iterador_ijk][0];
  }else{
    // Por defecto, el salto es cronológico hacia atrás
    this->iterador_ijk = this->iterador_ijk-1;
  }
  //Restaurar Dominios al punto saltarA
  this->ImagenDominioRestaurar_ijk(this->iterador_ijk);
  //Saltar
  this->IteradorSet_ijk(i,j,k);
  //cout << "Saltando a [" << this->iterador_ijk << "]: " << i << j << k << endl;
  if(!this->Conf_X[actual].empty()){
    //cout << this->Conf_X_detalle[actual][this->iterador_ijk] << endl;
  }

}
