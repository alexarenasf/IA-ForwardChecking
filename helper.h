using namespace std;
#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

class Helper {
  private:
    vector<pair<double,double> > position;
    string instancia;
    time_t tiempo_inicio;
  public:
    void LeerInstancia(string path,int &H,int &N,int &D,vector<int> &S,vector<vector<double> > &t, vector<double> &T);
    void LeerRutas(vector<vector<int> > &Ord_u, int N);
    
    void ReiniciarArchivos();
    void EscribirMejorSolucion(stringstream &best);
    void EscribirSolucionCandidata(stringstream &candidate,int score, string pois);
    void EscribirRuta(string ruta);
    
    double DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2);
    string Filename(const string& str);
    bool ArchivoExiste(const std::string& name);
    
    void TiempoIniciar();
    void TiempoGuardar(string evento,string sufijo);
};
