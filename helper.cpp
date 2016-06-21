using namespace std;
#include "helper.h"

void Helper::LeerInstancia(string path,int &H,int &N,int &D,vector<int> &S,vector<vector<double> > &t, vector<double> &T){

  int h_n, h_add, total, score;
  double x, y;
  
  ifstream read(path.c_str());
  read >> h_n;
  read >> h_add;
  read >> D;
  
  N = h_n - h_add - 1;
  H = h_n - N;
  
  read >> total;
  
  T.resize(D+1);
  
  for(int d = 1; d <= D; d++){
    read >> T[d];
  }
  
  this->position.resize(H+N+1);
  S.resize(H+N+1);
  t.resize(H+N+1);
 
  for(int i = 0; i <= H + N; i++){
    read >> x;
    read >> y;
    read >> score;
    
    this->position[i] = make_pair(x, y);
    S[i] = score;  
    t[i].resize(H+N+1);
    
    for(int j = 0; j <= H + N; j++){
      t[i][j] = 0.0;
    }
  }
  
  for(int i = 0; i <= H + N; i++){
    for(int j = 0; j <= H + N; j++){
      t[i][j] = this->DistanciaEuclidiana(this->position[i],this->position[j]);
    }
  }
  
  read.close();
  
  
  for(int i = 0; i <= H + N; i++){
    cout << "Origen " << i << ":" << endl;
    for(int j = 0; j <= H + N; j++){
      cout << "- Destino " << j << ": " << t[i][j] << endl;
    }
  }
}

void Helper::LeerRutas(vector<vector<int> > &Ord_u, int N){  
  int r;
  ifstream read("./tmp/rutas.tmp");
  
  Ord_u.clear();
  
  while(!read.eof()){    
    vector<int> ruta;
    for(int j = 0; j < N; j++){
      read >> r;
      ruta.push_back(r);
    }
    Ord_u.push_back(ruta);
  }
  read.close();
}

void Helper::ReiniciarArchivos(){
  ofstream rutas;
  rutas.open ("./tmp/rutas.tmp");
  rutas.close();
}

void Helper::EscribirRuta(string s){
  ofstream rutas;
  rutas.open ("./tmp/rutas.tmp", ios_base::app);
  rutas << s << endl;
  rutas.close();
}

void Helper::EscribirSolucion(){

}

double Helper::DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2){
  return sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
}

