using namespace std;
#include <iostream> 
#include <string>
#include <vector>

class ForwardChecking{
  private:
  //Parametros
    int H;
    int N;
    int D;
    vector<int> S;
    vector<vector<double> > t;
    vector<double> T;
  //Variables
    vector<vector<int> > X;
    vector<vector<int> > a;
  //Dominios
    vector<int> Dom_X;
    vector<vector<vector<int> > > Dom_instanciado_X;
    vector<vector<vector<int> > > Dom_iteracion_X;
  public:
    ForwardChecking(int hoteles, int pois, int dias, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist);
    void InitVariables();
    vector<int> Hoteles();
    vector<int> POIs();
    void MostrarInstancia();
    void MostrarDominio(int d, int i);
    void CrearDominio(int d, int i);
    void EliminarDominio(int d, int i, int l);
    void FiltrarDominio(int d, int i);
    bool EsPOI(int l);
    bool Instanciar(int d, int i);
    int CheckForward(int d, int i);
    int CBJ(int d, int i);
};
