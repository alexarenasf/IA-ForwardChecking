using namespace std;
#include "helper.h"
#include "forwardchecking.h"

int main(){
  string path = "./instances/SET0/32-65-1-2.ophs";
  Helper helper;

  int H;
  int N;
  int D;
  vector<int> S;
  vector<vector<double> > t;
  vector<double> T;

  helper.LeerInstancia(path, H, N, D, S, t, T);  
  ForwardChecking forwardchecking(H, N, D, S, t, T);
  forwardchecking.MostrarInstancia();
  
  return 0;
}