using namespace std;
#include <iostream> 
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

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
    vector<vector<vector<int> > > ImDom_X;
//Conjuntos de Conflictos 
    vector<vector<int> > Conf_u;
    vector<vector<int> > Conf_X;
//Iteradores para Variables X[i][j][k]
    vector<vector<int> > Ord_ijk;
    vector<vector<int> > Ord_u;
    unsigned int iterador_ijk;
    unsigned int iterador_u;
  public:
    ForwardChecking(int hoteles, int pois, int dias, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist);
    void SetRutas(vector<vector<int> > rutas);
    void InitVariables();
    vector<int> Hoteles();
    vector<int> POIs();
    
    void MostrarInstancia();
    void MostrarDia(int k);
    
//Operaciones para Dominio de X[i][j][k] = l
    void DominioFiltrar_X();
    void Dominio(int i, int j, int k);
    void Dominio_ijk();
    bool DominioVacio(int i, int j, int k);
    void DominioEliminar(int i, int j, int k, int l);
    int DominioPop(int i, int j, int k);
    bool DominioContiene(int i, int j, int k, int l);
    void ImagenDominioCrear_ijk(int ttt, int ijk);
    void ImagenDominioRestaurar_ijk(int ttt);

//Operaciones para el Conjunto Conflicto de X[i][j][k], ii > i, jj > j, kk > k
    void ConflictoAgregar_ijk(int iijjkk, int ijk);
    void ConflictoComer_ijk(int ijk, int iijjkk);
    
//Operaciones para Variable X[i][j][k]
    void IteradorCrear();
    void IteradorAvanzar(int &i, int &j, int &k);
    void IteradorRetroceder(int &i, int &j, int &k);
    void IteradorSet_ijk(int &i, int &j, int &k);
    bool IteradorPrimero();
    bool IteradorUltimo();
    void Instancia_X();
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
    string Ruta_u();
    bool Instanciar(int i);
    int CheckForward(int i);
    int CBJ(int i);
    
    
};
