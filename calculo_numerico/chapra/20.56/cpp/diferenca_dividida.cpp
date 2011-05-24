#include "diferenca_dividida.h"

#include <iostream>
using namespace std;

double DifDiv(const std::vector<double> *X, const std::vector<double> *Fx, int start, int end){
  if(end - start < 0){
    cerr << "start > end. INVALIDO!";
  }

  if(start == end){
    return (*Fx)[start];
  }
  else {
    return (DifDiv(X, Fx, start+1, end) - DifDiv(X, Fx, start, end-1)) / ((*X)[end] - (*X)[start]);
  }

}


//Calcula os coeficientes para a diferença dividida
std::vector<double> DiferencasDivididas(const std::vector<double> *X, const std::vector<double> *Fx)
{
  std::vector<double> coeficientes(X->size());
  coeficientes[0] = DifDiv(X, Fx, 0, 0);
  coeficientes[1] = DifDiv(X, Fx, 0, 1);
  coeficientes[2] = DifDiv(X, Fx, 0, 2);
  coeficientes[3] = DifDiv(X, Fx, 0, 3);
  coeficientes[4] = DifDiv(X, Fx, 0, 4);

  return coeficientes;
}



Matriz* DiferencasDivididasLinhas(const std::vector<double> *X, const Matriz *linhas)
{
  Matriz* coeficientes = new Matriz(linhas->size());
  for(int i =0; i < linhas->size(); i++){
    (*coeficientes)[i] = DiferencasDivididas(X, &(*linhas)[i]);
  }

  return coeficientes;
}


double FxInterpolado(double x, const std::vector<double> *X, const std::vector<double> *Fx)
{
  double FX0 = 0;
  double prod_difer = 1;

  if(X->size() != Fx->size()){
    cerr << "X and Fx have not the same size\n";
    return 0;
  }

  for(int i = 0; i < Fx->size(); i++){
    FX0 += prod_difer * (*Fx)[i];
    prod_difer = prod_difer * (x-(*X)[i]);
  }

  return FX0;
}

