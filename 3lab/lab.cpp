/****************************/
/* Lab work #3
/* Author: Nikolay Simotiuk
/* Group: КВ-51
/* Date:
/***************************/

#include <iostream>
#include <math.h>

#define N 4

using namespace std;

int printSystem(double m[][N + 1]) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j <= N; j++)
      if (j == N)
        cout << " = " << m[i][j] << endl;
      else if (m[i][j] != 0)
        cout << "+ " << m[i][j] << "*x" << j+1 << "\t";
    cout << endl;
  return 0;
}

int printMatrix(double m[][N + 1]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= N; j++)
      cout << m[i][j] << "\t\t";
    cout << endl;
  }
  cout << endl;
}

int fill(double m[][N + 1], int type) {
  double system[][N + 1] = {
    { 2, 11, 13, 15, 33 },
    { 12, 38, 18, 7, 114 },
    { 20, 1, 27, 5, 3 },
    { 15, 2, 15, 5, 6 }
  };

  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= N; j++) {
      m[i][j] = type == 0 ? 0 : system[i][j];
    }
  }
}

int pivoting(double m[][N + 1], double pivotLines[][N + 1], int count) {
  int max = fabs(m[0][0]);
  int p = 0, q = 0;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (fabs(m[i][j]) > max) {
        max = fabs(m[i][j]);
        p = i;
        q = j;
      }

  if (max == 0)
    return -1;

  for (int j = 0; j <= N; j++) {
    pivotLines[count][j] = m[p][j];

    // if it's not pivot line
    if (j != p && j < N) {
      double mi = - m[j][q] / m[p][q];

      // fill line
      for (int k = 0; k <= N; k++)
        if (m[j][k] != 0)
          m[j][k] += m[p][k] * mi;
    }
  }

  for (int j = 0; j < N; j++) {
    m[p][j] = 0;
    m[j][q] = 0;
  }

  return count != N - 1 ? pivoting(m, pivotLines, ++count) : 0;
}

int compl_piv(double m[][N + 1]) {
  double pivotLines[][N + 1] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }
  };
  // double pivotLines[][N + 1] = {
  //   { 0, 0, 0, 0 },
  //   { 0, 0, 0, 0 },
  //   { 0, 0, 0, 0 }
  // };
  pivoting(m, pivotLines, 0);

  double result[N];
  int roots[N]; // array of a root flags to indicate which roots already found
  for (int i = 0; i < N; i++) {
    result[i] = 0;
    roots[i] = 0;
  }

  for (int i = N - 1; i >= 0; i--) {
    double sum = 0;
    double value = 0;
    int indx;

    for (int j = 0; j < N; j++) {
      if (pivotLines[i][j] != 0 && roots[j] == 0) {
        value = pivotLines[i][j];
        indx = j;
      } else
        sum += pivotLines[i][j] * result[j];
    }

    result[indx] = (pivotLines[i][N] - sum) / value;
    roots[indx] = 1;
  }

  cout << "\nCOMPLETE PIVOTING METHOD:\n\n"
       << "Triangular matrix:\n";
       printSystem(pivotLines);

  cout << "Roots:\n";
  for (int i = 0; i < N; i++)
    cout << "x" << i + 1 << " = " << result[i] << ";\t\n";
  cout << endl;
  return 0;
}

int gauss_seidel(double m[][N + 1]) {
  double transformed[][N + 1] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 }
  };


  for (int i = 0; i < N; i++) {
    double bi = m[i][N] / m[i][i];
    cout << "bi = " << bi << endl;
    transformed[i][0] = bi;
    // for (int j = 0; j < N; j++) {
    // }
  }
  printMatrix(transformed);
}

int main() {
  double m[][N + 1] = {
    { 2, 11, 13, 15, 33 },
    { 12, 38, 18, 7, 114 },
    { 20, 1, 27, 5, 3 },
    { 15, 2, 15, 5, 6 }
  };
  // double m[][N + 1] = {
  //   { 4, 1, -2, 8 },
  //   { 1, -5, 1, -10 },
  //   { 3, 1, -5, 10 }
  // };

  cout << "Lab #3. Variant #15" << endl << endl
       << "Methods: complete pivoting and Gauss–Seidel" << endl
       << "System:\n";
  printSystem(m);

  compl_piv(m);
  fill(m, 1);
  gauss_seidel(m);

  return 0;
}

// схема з вибором головного елемента,  метод ітерації Зейделя