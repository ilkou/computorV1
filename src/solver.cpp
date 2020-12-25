#include <computor.h>

Solver::~Solver() {}

void Solver::start() {
  if (e->degree > 3)
    cout << "The polynomial degree is stricly greater than 2, I can't solve." << endl;
  else if (e->degree == 3)
    solveEq3d();
  else
    solveEq2d();
}

void Solver::solveEq2d() {
  if (e->a == 0.0) {
    if (e->b != 0.0) {
      if (details)
        cout << "a = 0 and b != 0, the solution is - c / b" << endl;
      cout << "The solution is:" << endl;
      printf("%lf\n", - e->c / e-> b);
    }
    else if (e->c == 0.0)
      cout << "all the real numbers are solution !" << endl;
    else
      cout << "No solution !" << endl;
  }
  else {
    double d = e->b * e->b - (4 * e->a * e->c);
    if (details)
      cout << "a != 0, Discriminant is D = b * b - 4 * a * c = " << d << endl;
    if (d > 0.0) {
      cout << "Discriminant is strictly positive, the two solutions are:" << endl;
      cout << (details ? "(- b - √D)/(2 * a) = " : "");
      printf("%lf\n", (-e->b - ft_sqrt(d)) / (2.0 * e->a));
      cout << (details ? "(- b + √D)/(2 * a) = " : "");
      printf("%lf\n", (-e->b + ft_sqrt(d)) / (2.0 * e->a));
    }
    else if (d == 0) {
      cout << "Discriminant is zero, the solution is:" << endl;
      cout << (details ? "(- b)/(2 * a) = " : "");
      printf("%lf\n", (-e->b) / (2.0 * e->a));
    }
    else {
      cout << "Discriminant is strictly negative, the two solutions are:" << endl;
      cout << (details ? "(- b - i * √D)/(2 * a) = " : "");
      printf("%lf %+lf * i\n", (-e->b) / (2.0 * e->a), (- ft_sqrt(-d)) / (2.0 * e->a));
      cout << (details ? "(- b + i * √D)/(2 * a) = " : "");
      printf("%lf %+lf * i\n", (-e->b) / (2.0 * e->a), ft_sqrt(-d) / (2.0 * e->a));
    }
  }
}

void Solver::solveEq3d() {
  double p = e->b - ((e->a * e->a) / 3.0);
  double q = (e->a * ((2.0 * (e->a * e->a)) - (9.0 * e->b)) / 27.0) + e->c;
  double k = ((q * q) / 4.0 ) + ((p * p * p) / 27.0);
  double u = ft_cbrt((-q / 2.0) + ft_sqrt(k));
  double v = ft_cbrt((-q / 2.0) - ft_sqrt(k));
  double c = - (((u + v) / 2.0) + (e->a / 3.0));
  cout << "the three solutions are:" << endl;
  printf("%lf\n", u + v - (e->a / 3.0));
  printf("%lf %+lf * i\n", c, -0.5 * ft_sqrt(3) * (u - v));
  printf("%lf %+lf * i\n", c, 0.5 * ft_sqrt(3) * (u - v));
}
