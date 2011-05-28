/*****************************************************************************
 * 20.56 Solution
 * Numerical Methods for Engineers, Chapra, 5th Ed.
 *****************************************************************************
 * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
 * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
 *****************************************************************************/

#ifndef __DIF_DIV_H__
#define __DIF_DIV_H__

#include <vector>
typedef std::vector< std::vector<double> > Matriz;

double DifDiv(const std::vector<double> *X, const std::vector<double> *Fx, int start, int end);
Matriz* DiferencasDivididasLinhas(const std::vector<double> *X, const Matriz *linhas);
std::vector<double> DiferencasDivididas(const std::vector<double> *X, const std::vector<double> *Fx);

double FxInterpolado(double x, const std::vector<double> *X, const std::vector<double> *Fx);


#endif
