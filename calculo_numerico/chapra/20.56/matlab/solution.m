%/*****************************************************************************
% * 20.56 Solution
% * Numerical Methods for Engineers, Chapra, 5th Ed.
% *****************************************************************************
% * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
% * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
% * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
% *****************************************************************************/

clc

fprintf('------------------------------\n');
fprintf('Chapra, Ex. 20.56\n');
fprintf('------------------------------\n');

% Dados do problema
X = 0:2:8;
Y = 0:2:8;
Fxy = [
  100.00  90.00   80.00   70.00   60.00;
  85.00   64.49   53.50   48.15   50.00;
  70.00   48.90   38.43   35.04   40.00;
  55.00   38.78   30.39   27.07   30.00;
  40.00   35.00   30.00   25.00   20.00
];

% Inicializacao de variaveis
Fy = zeros(1, size(Y, 2));

% Entrada do Usuario
x = input('X = ');
y = input('Y = ');


% Solução
for i=1:size(Y, 2)
  tmp = diferencas_divididas(X, Fxy(i,:));
  Fy(end,i) = interpolacao_dif_div(x, X, diag(tmp));
end

tmp = diferencas_divididas(Y, Fy);
T = interpolacao_dif_div(y, Y, diag(tmp));

fprintf('T(%f, %f) = %f\n', x, y, T);