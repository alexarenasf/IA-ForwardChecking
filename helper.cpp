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
  
  T.resize(D);
  
  for(int d = 0; d < D; d++){
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
  
}

double Helper::DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2){
  return sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
}

void Helper::EscribirSolucion(){

}