using namespace std;
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

class Helper {
  private:
    vector<pair<double,double> > position;
  public:
    void LeerInstancia(string path,int &H,int &N,int &D,vector<int> &S,vector<vector<double> > &t, vector<double> &T);
    void LeerRutas(vector<vector<int> > &Ord_u, int N);
    
    void ReiniciarArchivos();
    void EscribirSolucion();
    void EscribirRuta(string ruta);
    
    double DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2);
};
