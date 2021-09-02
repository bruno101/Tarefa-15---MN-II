#include <iostream>
#include <vector>
using namespace std;


vector<double> substituicoesRetroativas (int n, vector<vector<double>> A, vector<double> b) {

  vector<double> x (n);

  x[n-1] = b[n-1]/A[n-1][n-1];
  for (int i = n-2; i >= 0; i--) {
    double soma = 0;
    for (int j = i+1; j <= n-1; j++) {
      soma = soma + A[i][j]*x[j];
    }
    x[i] = (b[i] - soma)/A[i][i];
  }

  return x;

}

vector<double> eliminacaoDeGauss (int n, vector<vector<double>> A, vector<double> b) {

  for (int k = 0; k <= n-2; k++) {
    for (int i = k+1; i <= n-1; i++) {
      double m = - A[i][k]/A[k][k];
      A[i][k] = 0;
      for (int j = k+1; j <= n-1; j++) {
        A[i][j] = A[i][j] + m*A[k][j];
      }
      b[i] = b[i] + m*b[k];
    }
  }

  return substituicoesRetroativas(n, A, b);

}

void q1() {

  int N = 8;
  double y_at0 = 0.0;
  double y_at1 = 1.0;

  double x = 1.0/N;
  vector<vector<double>> M(N-1, vector<double>(N-1));
  vector<double> v(N-1), y(N-1);

  for (int i = 0; i < N-1; i++) {

    M[i][i] = -(1.0 + 2.0/(x*x));
    if (i > 0) {
      M[i][i-1] = 1.0/(x*x);
    }
    if (i < N-2) {
      M[i][i+1] = 1.0/(x*x);
    }

  }

  v[0] = -y_at0*(1.0/(x*x));
  v[N-2] = -y_at1*(1.0/(x*x));
  y = eliminacaoDeGauss(N-1, M, v);

  cout << "Soluções:\n";

  for (int i = 0; i < N-1; i++) {
    cout << "y_" << i+1 << ": " << y[i] << "\n";
  }

}

double f(double x, double y) {
  return 4;
}

void q2 () {

  int N = 4;
  double u_atx0 = 0;
  double u_atx1 = 0;
  double u_aty0 = 0;
  double u_aty1 = 0;

  double x = 1.0/N;
  int tamM = (N-1)*(N-1);
  vector<vector<double>> M(tamM, vector<double>(tamM));
  vector<double> v(tamM), y(tamM);

  for (int i = 0; i < tamM; i++) {

    M[i][i] = -2.0*(2.0/(x*x));
    if (i%(N-1) != 0) {
      M[i][i-1] = 1/(x*x);
    }
    if (i%(N-1) != 2) {
      M[i][i+1] = 1/(x*x);
    }
    if (i > N-2) {
      M[i][i-N+1] = 1/(x*x);
    }
    if (i < tamM-N+1) {
      M[i][i+N-1] = 1/(x*x);
    }

    v[i] = f(i,i);

  }


  y = eliminacaoDeGauss(tamM, M, v);

  cout << "Soluções:\n";

  for (int i = 0; i < tamM; i++) {
    cout << "y_" << i+1 << ": " << y[i] << "\n";
  }

}

int main() {

  int num_questao = 2;

  if (num_questao == 1) {
    q1();
  } else {
    q2();
  }

}