using namespace std;
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>

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
    vector<vector<vector<int> > > X;
    vector<int> u;
//Dominios
    vector<vector<vector<vector<int> > > > Dom_X;
    vector<vector<int> > Dom_u;
//Imagnes de Dominios
    vector<vector<vector<int> > > ImDom_u;
//Conjuntos de Conflictos 
    vector<vector<int> > Conf_u;
  public:
    ForwardChecking(int hoteles, int pois, int dias, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist);
    void InitVariables();
    vector<int> Hoteles();
    vector<int> POIs();
    
    void MostrarInstancia();
    void MostrarDia(int k);
    
//Operaciones para Dominio de X[i][j][k] = l
    void DominioFiltrar_X();
    void Dominio(int i, int j, int k);
    bool DominioVacio(int i, int j, int k);
    void DominioEliminar(int i, int j, int k, int l);
    int DominioPop(int i, int j, int k);
    bool DominioContiene(int i, int j, int k, int l);
    
//Operaciones para Variable X[i][j][k]
    bool Instanciar(int i, int j, int k);
    void CheckForward(int &i, int &j, int &k);
    void CBJ(int &i, int &j, int &k);
    
//Operaciones para Dominio de u[i] = n
    void Dominio(int i);
    bool DominioVacio(int i);
    int DominioPop(int i);
    void DominioEliminar(int i, int n);
    bool DominioContiene(int i, int n);
    void ImagenDominioCrear(int t, int i);
    void ImagenDominioRestaurar(int t);

//Operaciones para el Conjunto Conflicto de u[i], ii > i
    void ConflictoAgregar(int ii, int i);
    void ConflictoComer(int i, int ii);
    
//Operaciones para Variable u[i]
    void Instancia_u();
    bool Instanciar(int i);
    int CheckForward(int i);
    int CBJ(int i);
    
    
};
