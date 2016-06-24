using namespace std;
#include "forwardchecking.h"

void ForwardChecking::IteradorCrear(){
  vector<int> ijk;
  ijk.resize(3);
  
  this->Ord_ijk.clear();
    
  for(int k = 1; k <= this->D; k++){
    for(int i = 0; i <= this->H; i++){      
      for(int j = 0; j < this->N; j++){
        ijk[0]=i;
        ijk[1]=this->Ord_u[this->iterador_u][j];
        ijk[2]=k;

        this->Ord_ijk.push_back(ijk);
      }
      for(int j = 0; j <= this->H; j++){
        ijk[0]=i;
        ijk[1]=j;
        ijk[2]=k;

        this->Ord_ijk.push_back(ijk);
      }
    }
    
    for(int i = 0; i < this->N; i++){
      
      for(int j = 0; j < this->N; j++){
        ijk[0]=this->Ord_u[this->iterador_u][i];
        ijk[1]=this->Ord_u[this->iterador_u][j];
        ijk[2]=k;

        this->Ord_ijk.push_back(ijk);
      }
      
      for(int j = 0; j <= this->H; j++){
        ijk[0]=this->Ord_u[this->iterador_u][i];
        ijk[1]=j;
        ijk[2]=k;

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

bool ForwardChecking::Instancia_X(Helper helper){
  int i,j,k;
  
  stringstream solucion;
  
  //Verificar Restricciones
  // Destino es hotel 1
  int suma_destino_1 = 0;
  for(int i = 0; i <= this->H + this->N; i++){
    suma_destino_1 += this->X[i][1][this->D];
  }
  
  if(suma_destino_1 == 0)
    return false;
    
  // Origen es hotel 0
  int suma_origen_0 = 0;
  for(int j = 0; j <= this->H + this->N; j++){
    suma_origen_0 += this->X[0][j][1];
  }
  
  if(suma_origen_0 == 0)
    return false;
  
  
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
      return false;
  }
  
  
  //Todos los días terminan en un hotel
  for(int k = 1; k<=this->D; k++){
    int suma_destino = 0;
    for(int h = 0; h <= this->H; h++){
      for(int i = 0; i <= this->H + this->N; i++){
        suma_destino += this->X[i][h][k];
      }
    }
    
    if(suma_destino == 0)
      return false;
  }
  
  
  //Todos los empiezan en un hotel terminan en un hotel
  for(int k = 1; k<=this->D; k++){
    int suma_origen = 0;
    for(int h = 0; h <= this->H; h++){
      for(int j = 0; j <= this->H + this->N; j++){
        suma_origen += this->X[h][j][k];
      }
    }
    
    if(suma_origen == 0)
      return false;
  }
  
  //Continuidad en la ruta
  bool primero = true;
  int j_ant;
  for(unsigned int ijk = 0; ijk < this->Ord_ijk.size(); ijk++){
    i = this->Ord_ijk[ijk][0];
    j = this->Ord_ijk[ijk][1];
    k = this->Ord_ijk[ijk][2];
    
    if(this->X[i][j][k] == 1){
      if(!primero && j_ant != i){
        return false;
      }
      
      primero = false;
      j_ant = this->Ord_ijk[ijk][1];
    }
  }
  
  
  //Tiempo Maximo
  vector<double> t;
  t.resize(this->D+1);
  bool exesotiempo = false;
  double distancia_total = 0;
  
  for(int k = 1; k<=this->D; k++){
    t[k] = 0;
    for(int i = 0; i <= this->H + this->N; i++){
      for(int j = 0; j <= this->H + this->N; j++){
        t[k]+=this->t[i][j]*this->X[i][j][k];
        distancia_total += this->t[i][j]*this->X[i][j][k];
      }
    }
        
    if(t[k] > this->T[k])
      exesotiempo = true;
  }
  
  if(exesotiempo)
    return false;
  
  for(int k = 1; k<=this->D; k++){
    cout << "t[" << k << "] = " << t[k] << " ";
  }
  
  // Calcular el Score
  int score = 0;
  for(int k = 1; k<=this->D; k++){
    for(int i = 0; i <= this->H + this->N; i++){
      for(int j = 0; j <= this->H + this->N; j++){
        score += this->S[i]*this->X[i][j][k];
      }
    }
  }
  
  cout << " | " << score ;
  
  vector<int> k_hotel_inicial;
  vector<int> k_hotel_final;
  vector<vector<int> > k_trip;
  
  k_hotel_inicial.resize(this->D+1);
  k_hotel_final.resize(this->D+1);
  k_trip.resize(this->D+1);
  
  //Mostrar la Instancia
  int k_ant = -1;
  for(unsigned int ijk = 0; ijk < this->Ord_ijk.size(); ijk++){
    i = this->Ord_ijk[ijk][0];
    j = this->Ord_ijk[ijk][1];
    k = this->Ord_ijk[ijk][2];

    if(this->X[i][j][k] == 1){
      if(k!=k_ant){
        cout <<  " | " << i << "->" << j;
        k_hotel_inicial[k] = i;
        if(j>this->H)
          k_trip[k].push_back(j);
      }else{
        cout << "->" << j;
        if(j>this->H)
          k_trip[k].push_back(j);
        if(j<=this->H)
          k_hotel_final[k] = j;
      }
      
      k_ant = k;
    }
    
    
  }
  cout << endl;
  
  stringstream pois;
  solucion.str(string());
  
  solucion << distancia_total << " " << score << endl; 
  pois << "POIS";
  
  for(int k=1; k<=this->D; k++){
    solucion << this->T[k] << " " << t[k] << " " << k_hotel_inicial[k] << " " << k_hotel_final[k];
    for(unsigned int t = 0; t < k_trip[k].size(); t++){
      solucion << " " << k_trip[k][t];
      pois << "-" << k_trip[k][t];
    }
    solucion << endl;
  }
  solucion << endl;
  
  //Guardar solución candidata
  string solucionstr = solucion.str();
  helper.EscribirSolucionCandidata(solucion,score,pois.str());
  solucion.str(solucionstr);
  
  //Guardar mejor solución
  if(score >= this->mejor_score){
    this->mejor_score = score;
    helper.EscribirMejorSolucion(solucion);
  }
  
  
  
  return true;
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
  if(this->DominioVacio(i,j,k))
    return false;
    
  //Preimagen para otras variables
  for(unsigned ijk = this->iterador_ijk + 1; ijk < this->Ord_ijk.size(); ijk++){
    if(ijk != this->iterador_ijk)
      this->ImagenDominioCrear_ijk(this->iterador_ijk,ijk);
  }
    
  this->X[i][j][k] = this->DominioPop(i,j,k);
  
  // Despues de instanciar un arco conectado (this->X[i][j][k] == 1), recalcular tiempo acumulado
  if(this->X[i][j][k] == 1){
    // Si el destino es hotel, el tiempo se reinicia
    if(j <= this->H){
      this->A_X[this->iterador_ijk] = 0;
    // Si es POI, el tiempo se acumula
    }else{
      if(this->iterador_ijk>0)
        this->A_X[this->iterador_ijk] = this->A_X[this->iterador_ijk-1] + this->t[i][j];
      else
        this->A_X[this->iterador_ijk] = this->t[i][j];
    }
  // Si no se conecta el arco, entonces el tiempo no cambia en relación a la iteración anterior 
  }else{
    if(this->iterador_ijk>0)
      this->A_X[this->iterador_ijk] = this->A_X[this->iterador_ijk-1];
  }

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

  vector <int> posteriores;
  
  if(destinoEsPoi){
// Buscar posteriores al poi actual en la ruta
    int r;

    for(unsigned int u = 0; u < this->Ord_u[this->iterador_u].size(); u++){
      if(this->Ord_u[this->iterador_u][u] == j){
        r = u+1;
      }
    }

    for(unsigned int u = r; u < this->Ord_u[this->iterador_u].size(); u++){
      posteriores.push_back(this->Ord_u[this->iterador_u][u]);
    }

      //cout << endl;
  }
  
  
  double distancia_disponible = this->T[k] - this->A_X[this->iterador_ijk];
  int puedo_llegar_a = 0;
  int puedo_llegar_a_hotel = 0;
  
  for(unsigned ijk = this->iterador_ijk + 1; ijk < this->Ord_ijk.size(); ijk++){
    ii = this->Ord_ijk[ijk][0];
    jj = this->Ord_ijk[ijk][1];
    kk = this->Ord_ijk[ijk][2];
      
   if(visitar_ijk == 1){       
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
      
// Al visitar un destino, se deben filtrar todos los destinos inaccesibles por distancia
// Para todos los origenes futuros ii iguales al destino actual j en el mismo día futuro kk igual al día actual k
    if(ii == j && kk == k && j != jj){
      if(distancia_disponible < t[ii][jj]){
        if(this->DominioEliminar(ii,jj,kk,1)){
          // La variable futura ijk ahora tiene conflictos con this->iterador_ijk (actual)
          this->ConflictoAgregar_ijk(ijk,this->iterador_ijk);
          
          //Si el dominio de la variable ii > i, jj > j, kk > k queda vacío, copiar el conjunto conflicto de ii,jj,kk en ijk, despues probar con otro valor para ijk
          if(this->DominioVacio(ii,jj,kk)){
            this->ConflictoComer_ijk(this->iterador_ijk,ijk);
            dominioAniquilado = true;
          }
        }

      }else{
        if(jj <= this->H)
          puedo_llegar_a_hotel++;
        puedo_llegar_a++;
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

    }
  }
  
  if((puedo_llegar_a == 0 || puedo_llegar_a_hotel == 0) && visitar_ijk == 1){
    for(unsigned ijk = this->iterador_ijk + 1; ijk < this->Ord_ijk.size(); ijk++){
      ii = this->Ord_ijk[ijk][0];
      jj = this->Ord_ijk[ijk][1];
      kk = this->Ord_ijk[ijk][2];
      
      if(k == kk){
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
  }
  
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
