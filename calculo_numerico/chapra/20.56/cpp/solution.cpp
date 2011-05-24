#include "diferenca_dividida.h"

/*****************************************************************************
 * 20.56 Solution
 * Numerical Methods for Engineers, Chapra, 5th Ed.
 *****************************************************************************
 * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
 * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
 * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
 *****************************************************************************/

//#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  float x, y, Fxy;

  //
  //Inicialização dos Dados
  //
  Matriz dados(5);
  for(int i=0; i < dados.size(); i++){
    dados[i].resize(5);
  }

  dados[0][0] = 100.0;
  dados[0][1] = 90.0;
  dados[0][2] = 80.0;
  dados[0][3] = 70.0;
  dados[0][4] = 60.0;

  dados[1][0] = 85.0;
  dados[1][1] = 64.49;
  dados[1][2] = 53.5;
  dados[1][3] = 48.15;
  dados[1][4] = 50.0;

  dados[2][0] = 70.0;
  dados[2][1] = 48.90;
  dados[2][2] = 38.43;
  dados[2][3] = 35.03;
  dados[2][4] = 40.0;

  dados[3][0] = 55.0;
  dados[3][1] = 38.78;
  dados[3][2] = 30.39;
  dados[3][3] = 27.07;
  dados[3][4] = 30.0;

  dados[4][0] = 40.0;
  dados[4][1] = 35.0;
  dados[4][2] = 30.0;
  dados[4][3] = 25.0;
  dados[4][4] = 20.0;

  //Valores de X
  vector<double> X(5);
  X[0] = 0.0;
  X[1] = 2.0;
  X[2] = 4.0;
  X[3] = 6.0;
  X[4] = 8.0;
  
  //Valores de Y
  vector<double> Y(5);
  Y[0] = 0.0;
  Y[1] = 2.0;
  Y[2] = 4.0;
  Y[3] = 6.0;
  Y[4] = 8.0;

  cout << "------------------------------\n";
  cout << "Chapra, Ex. 20.56\n";
  cout << "------------------------------\n";

  cout << "X = ";
  cin >> x;

  cout << "Y = ";
  cin >> y;

  //Diferenças Divididas por Linha
  Matriz* DifDivY = DiferencasDivididasLinhas(&X, &dados);

  //Vetor de polinômios por Interpolação: F(x0, y)
  //Cria um novo gráfico onde os pontos são interpolações de X0 em cada Y definido
  std::vector<double> FX0(Y.size());
  for(int i=0; i < FX0.size(); i++){
    FX0[i] = FxInterpolado(x, &X, &(*DifDivY)[i]);
  }

  //Cria um novo polinômio por Interpolação: F(x0, Y0)
  std::vector<double> DifDivX = DiferencasDivididas(&Y, &FX0);

  //Avalia o polinômio por Interpolação em y0
  Fxy = FxInterpolado(y, &Y, &DifDivX);
  cout << "T(" << x << ", " << y << ") = " << Fxy << "\n";

  return 0;
}

