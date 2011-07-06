%/*****************************************************************************
% * P29.7
% * Solution using LU decomposition and Gauss-Seidel methods.
% * Numerical Methods for Engineers, Chapra, 5th Ed.
% *****************************************************************************
% * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
% * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
% * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
% *****************************************************************************/

%dim = pontos internos
clc;
[M, S] = criaMatrizPrecisao( 5.0, 100.0 );

% M
% S

fprintf('\n *** Resolvendo por LU [ dim = 5.0 e T(max) = 100 ] ***\n');

%Cria os L e U (apenas 1 vez para cada h, pois ele determina M)
[L U P] = lu(M);

%Resolve
d = P * S;
y = L \ d;
X = U \ y



fprintf('\n *** Resolvendo por Gauss-Seidel \\ S [ dim = 5.0 e T(max) = 100 ] ***\n');

X = gauss_seidel( M, S, 1000, 0.0001 ) %com erro 0.00001 ele acha o valor exato



fprintf('\n *** Resolvendo por X = M \\ S [ dim = 5.0 e T(max) = 100 ] ***\n');

X = M \ S

