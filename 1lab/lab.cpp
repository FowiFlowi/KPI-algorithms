/****************************/
/* Lab work #1
/* Author: Nikolay Simotiuk
/* Group: КВ-51
/* Date: 3.10.2017
/***************************/

#include <iostream>
#include <math.h>
#include <stdlib.h> 

using namespace std;

double mySin(double x, double eps, double un, int k, int sign, double result, double *rest, int *n, double &res) {
  if (fabs(un) < eps) {
    *rest = un;
    res = result;
    return result;
  }
  result += un * sign;
  un *= x*x / (2*k * (2*k + 1));
  sign = -sign;
  *n += 1;
  mySin(x, eps, un, k + 1, sign, result, rest, n, res);
}

double mySinN(double x, int n, int sign, double *rest, double un, int k, double result, double &res) {
  if (k >= n) {
    *rest = un;
    res = result;
    return result;
  }
  result += un * sign;
  un *= x*x / (2*k * (2*k + 1));
  sign = -sign;
  mySinN(x, n, sign, rest, un, k + 1, result, res);
}

int lab(double a, double b) {
  double x = (b + a) / 2;
  double rest;
  int n = 0;

  double delta[10]; // arrays for the second task
  double rests[10];
  double xi[10];

  cout << "Lab #1. 15 Variant\nFunction: sin(x). Interval: [" << a << "; " << b << "]\n\n";
  cout << "epsilon\tnum\tdelta\t\trest\n";
  for (double eps = 1e-2; eps >= 1e-14; eps *= 1e-3) {
    double res;
    mySin(x, eps, x, 1, 1, 0, &rest, &n, res);
    cout << eps << '\t'
         << n << '\t'
         << sin(x) - res << '\t'
         << rest << endl;

    if (eps == 1e-8) {
      double h = (b - a) / 10;
      for (int i = 0; i < 11; i++) {
        double x = a + h * i;
        double restN;
        mySinN(x, n, 1, &restN, x, 1, 0, res);
        delta[i] = sin(x) - res;
        rests[i] = restN;
        xi[i] = x;
      }
    }
  }

  cout << "\n\nXi\t\tdelta\t\trest\n";
  for (int i = 0; i < 11; i++) {
    cout << xi[i] << "\t\t"
         << delta[i] << "\t"
         << rests[i] << endl;
  }
}

int main() {
  double a = 0.33;
  double b = 7.4;

  lab(a, b);
}