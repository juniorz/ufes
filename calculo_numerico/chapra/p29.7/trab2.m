% Chapra, P29.7

[M, S] = criaMatriz( 5.0, 100.0 );

% M
% S



clc;
fprintf('\n *** Resolvendo por LU [ dim = 5.0 e T(max) = 100 ] ***\n');

%Cria os L e U (apenas 1 vez para cada h, pois ele determina M)
[L U P] = lu(M);

%Resolve
d = P * S;
y = L \ d;
X = U \ y



fprintf('\n *** Resolvendo por Gauss-Seidel \\ S [ dim = 5.0 e T(max) = 100 ] ***\n');

X = gauss_seidel( M, S, 50, 0.0001 ) %com erro 0.00001 ele acha o valor exato



fprintf('\n *** Resolvendo por X = M \\ S [ dim = 5.0 e T(max) = 100 ] ***\n');

X = M \ S







fprintf('\n *** Resolvendo por LU (sem recalcular o LU) [ dim = 5.0 e T(max) = 120 ] ***\n');

[X, S] = criaMatriz( 5.0, 120.0 );
d = P * S;
y = L \ d;
X = U \ y



fprintf('\n *** Resolvendo por Gauss-Seidel \\ S [ dim = 5.0 e T(max) = 100 ] ***\n');

X = gauss_seidel( M, S, 50, 0.0001 ) %com erro 0.00001 ele acha o valor exato



fprintf('\n *** Resolvendo por X = M \\ S [ dim = 5.0 e T(max) = 120 ] ***\n');

X = M \ S

