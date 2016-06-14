using namespace std;
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Helper {
  private:
    vector<pair<double,double> > position;
  public:
    void LeerInstancia(string path,int &H,int &N,int &D,vector<int> &S,vector<vector<double> > &t, vector<double> &T);
    double DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2);
    void EscribirSolucion();
};