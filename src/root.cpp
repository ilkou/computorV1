#include <stdio.h>
#include <math.h>
#include <string>

/* 
	Special cases:
 *	sqrt(+-0) = +-0 	... exact
 *	sqrt(inf) = inf
 *	sqrt(-ve) = NaN		... with invalid signal
 *	sqrt(NaN) = NaN		... with invalid signal for signaling NaN
*/
static int		ft_isqrt(int nb)
{
	int root;

	root = 1;
	while (root <= nb / 2)
	{
		if ((root * root) >= nb)
			return (root);
		root++;
	}
	return (root);
}

/*
 * http://villemin.gerard.free.fr/ThNbDemo/Heron.htm#algo
*/
double	ft_sqrt(double x) {
	double r;
	double root = x <= 1 || x > 214748364 ? x : (double)ft_isqrt(x);
	int i = -1;
	
	if (x == 0 || isnan(x) || isinf(x) || x == 1)
		return (x);
	else if (root * root == x)
		return (root);
	else if (x < 0)
		return (NAN);
	while (++i != -1) {
		r = 0.5 * (root + (x / root));
		if (abs(r - root) < 0.0000001)
			break ;
		root = r;
	}
	return (root);
}

/*
 * https://fr.wikipedia.org/wiki/Algorithme_de_calcul_de_la_racine_n-i%C3%A8me
*/
double	ft_cbrt(double x) {
	double r;
	double root = x;
	int i = -1;
	
	if (x == 0 || isnan(x) || isinf(x) || x == 1)
		return (x);
	else if (x < 0)
		return (NAN);
	while (++i != -1) {
		r = (2 * root + (x / (root * root))) / 3.0;
		if (abs(r - root) < 0.0000001)
			break ;
		root = r;
	}
	return (root);
}

/*int main(int argc, char **argv) {
	
	if (argc > 1) {
		double x = std::stod(argv[1]);
		double mySqrt = ft_cbrt(x);
		double normalSqrt = cbrt(x);
		printf("ft_sqrt(%s) = %.20lf\n", argv[1], mySqrt);
		printf("sqrt(%s)    = %.20lf\n", argv[1], normalSqrt);
		printf("error: %.10lf\n", abs(mySqrt - normalSqrt));
	}

	return (0);
}*/