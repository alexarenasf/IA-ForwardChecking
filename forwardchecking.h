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
    vector<vector<vector<bool> > > X;
    vector<int> u;
  public:
    ForwardChecking(int hotels, int pois, int days, vector<int> scores, vector<vector<double> > dist, vector<double> maxdist);
    void InitVariables();
    void MostrarInstancia();
};