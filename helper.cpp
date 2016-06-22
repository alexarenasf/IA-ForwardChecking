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
  
  this->instancia = this->Filename(path);
  cout << this->instancia << endl;
  
  
  //~ for(int i = 0; i <= H + N; i++){
    //~ cout << "Origen " << i << ":" << endl;
    //~ for(int j = 0; j <= H + N; j++){
      //~ cout << "- Destino " << j << ": " << t[i][j] << endl;
    //~ }
  //~ }
  
  
}

void Helper::LeerRutas(vector<vector<int> > &Ord_u, int N){  
  int r;
  stringstream path;
  path << "./tmp/";
  path << this->instancia;
  path << ".routes";
  
  ifstream read(path.str().c_str());
  
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
  stringstream path;
  path << "./tmp/";
  path << this->instancia;
  path << ".routes";
  
  ifstream read(path.str().c_str());
  ofstream rutas;
  rutas.open (path.str().c_str());
  rutas.close();
}

void Helper::EscribirRuta(string s){
  stringstream path;
  path << "./tmp/";
  path << this->instancia;
  path << ".routes";
  
  ofstream rutas;
  rutas.open (path.str().c_str(), ios_base::app);
  rutas << s << endl;
  rutas.close();
}

void Helper::EscribirMejorSolucion(stringstream &best){
  stringstream path;
  time_t timer;
  time(&timer);
  
  path << "./out/";
  path << this->instancia;
  path << ".out";
  
  ofstream sol;
  sol.open (path.str().c_str());
  sol << best.rdbuf();
  sol.close();
}

void Helper::EscribirSolucionCandidata(stringstream &candidate,int score, string pois){
  stringstream path;
  time_t timer;
  time(&timer);
  
  path << "./candidates/";
  path << this->instancia;
  path << "_";
  path << score;
  path << "_" << pois;
  path << ".out";
  
  ofstream sol;
  sol.open (path.str().c_str());
  sol << candidate.rdbuf();
  sol.close();
}

void Helper::TiempoIniciar(){
  time(&this->tiempo_inicio);
}

void Helper::TiempoGuardar(string evento){
  stringstream path;
  time_t timer;
  time(&timer);
  
  path << "./tmp/";
  path << this->instancia;
  path << ".time";
  
  ofstream times;
  times.open (path.str().c_str(), ios_base::app);
  times << difftime(timer,this->tiempo_inicio);
  times << " " << evento << endl;
  times.close();
}

double Helper::DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2){
  return sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
}

string Helper::Filename (const string& str){
  size_t found = str.find_last_of("/\\");
  size_t found_extension = str.find_last_of(".");
  return str.substr(found+1,found_extension-found-1);
}

