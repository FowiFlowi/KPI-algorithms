/****************************/
/* Lab work #2
/* Author: Nikolay Simotiuk
/* Group: КВ-51
/* Date: 27.10.2017
/***************************/

#include <iostream>
#include <math.h>

using namespace std;

double f(double x) {
  return 15 / x - x*x + 15;
}
double f_(double x) {
  return - 2*x - 15 / (x*x);
}

int bisection(double result[3], double a, double b, double eps, int count) {
  double c = (a + b) / 2;
  
  if (fabs(a - b) < 2*eps) {
    result[0] = c;
    result[1] = count;
    result[2] = (b - a) / 2;
    return 0;
  }

  return f(a) * f(c) < 0 ? bisection(result, a, c, eps, ++count) 
                         : bisection(result, c, b, eps, ++count);
}

int successive(double result[3], double a, double b, double eps, double lambda, double q, double x0, double xk, int count) {
  if (fabs(xk - x0) <= (1 - q)/q * eps) {
    result[0] = xk;
    result[1] = count;
    result[2] = fabs(xk - x0) * q/(1 - q);
    return 0;
  }

  x0 = xk;
  xk = x0 - lambda * f(x0);
  return successive(result, a, b, eps, lambda, q, x0, xk, ++count);
}

double succ_appr(double result[3], double a, double b, double eps) {
  double lambda, q;

  double m1 = fabs(f_(a));
  double M1 = fabs(f_(b));

  if (m1 > M1) {
    q = 1 - (M1 / m1);
    lambda = 1 / f_(a);
  } else {
    q = 1 - (m1 / M1);
    lambda = 1 / f_(b);
  }

  double x0 = a + eps;
  double xk = lambda < 0 ? x0 + lambda * f(x0) 
                         : x0 - lambda * f(x0);

  return successive(result, a, b, eps, lambda, q, x0, xk, 1);
}

int main() {
  double intervals[6] = { -3.5, -3, -1.5, -1, 4, 4.5 };

  cout << "Lab #2. Variant #15" << endl << endl
       << "Equation: 15/x - x^2 + 15 = 0" << endl
       << "f (x) = 15 / x - x*x + 15" << endl
       << "f'(x) = - 2*x - 15 / (x^2)" << endl
       << "Methods: bisection and successive approximations" << endl
       << "intervals: [-3.5, -3]; [-1.5, -1]; [4, 4.5];" << endl << endl;

  for (int j = 0; j < sizeof(intervals)/sizeof(*intervals); j += 2) {
    double a = intervals[j];
    double b = intervals[j + 1];
    double eps = 0.01;

    cout << " Interval: [" << a << ", " << b << ']' << endl
         << "\t|\tSUCCESSIVE APPROXIMATIONS\t|\t\tBISECTION" << endl
         << " eps\t|root\t\t|accuracy\t|count\t|root\t\t|accuracy\t|count\t" << endl
         << "-------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < 3; i++) {
      double sRes[3], bRes[3];
      
      succ_appr(sRes, a, b, eps);
      bisection(bRes, a, b, eps, 1);

      cout << eps << "\t|" << sRes[0] << "\t|" << sRes[2] << "\t|" << sRes[1] << "\t|" 
           << bRes[0] << "\t| " << bRes[2] << "\t| " << bRes[1] << endl;

      eps *= 0.001;
    }
    cout << endl << endl;
  }

  return 0;
}