/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:24:23 by oouklich          #+#    #+#             */
/*   Updated: 2020/11/18 17:13:26 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor.h>

bool details;

static void		displayUsage(const char *exec) {
	printf("usage: %s \"polynomial equation of degree less than or equal to 2\"\n\n", exec);
	printf("For example:\n");
	printf("       %s \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"\n", exec);
	printf("For details:\n");
	printf("       %s \"1337 * X^0 = 1337 * X^0\" -details\n", exec);
	exit(EXIT_FAILURE);
}

static void		computorv1(const char *eq) {
	Equation e;

	e.parseEquation(eq);
	e.setCoefs();
	e.displayReducedForm();
	e.displayDegree();
	Solver s(&e);
	s.start();
}

int				main(int argc, char **argv) {
	details = false;
	if (argc == 1 || argc > 3)
		displayUsage(argv[0]);
	if (argc == 3) {
		if (strcmp(argv[2], "-details") == 0)
			details = true;
		else
			displayUsage(argv[0]);
	}
	computorv1(argv[1]);
	return (EXIT_SUCCESS);
}
