/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouklich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:17:11 by oouklich          #+#    #+#             */
/*   Updated: 2020/11/06 14:27:58 by oouklich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
#define COMPUTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <regex>

using namespace std;

#include <equation.h>
#include <solver.h>

double	ft_sqrt(double x);
double	ft_cbrt(double x);

Node* newNode(double coef, int power);
string removeSpaces(string str);

extern bool details;

#endif
