% Gauss-Seidel Method
% Solves Mx = b

function x = gauss_seidel( M, b, N, e )
  %/*****************************************************************************
  % * P29.7
  % * Solution using LU decomposition and Gauss-Seidel methods.
  % * Numerical Methods for Engineers, Chapra, 5th Ed.
  % *****************************************************************************
  % * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
  % * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
  % * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
  % *****************************************************************************/
  % Original code from: https://ece.uwaterloo.ca/~dwharder/NumericalAnalysis/04LinearAlgebra/gauss/
  % Typo fixes by Reinaldo de Souza Junior (2011)

  % The diagonal entries of M and their inverses
	n = length( b );
	d = diag( M );

	if ~all( d ) 
		error 'at least one diagonal entry is zero';
	end

	invd = d.^-1;
	% Matrix of off-diagonal entires of N
	Moff = M - diag( d );

	% Use d.^-1*b as the first approximation to x
	invdb = invd.*b;
	x = invdb; %there was a typo here

	%              -1
	% Iterate x = D  (b - M   *x)
	%                      off
	for k = 1:N
		xprev = x;

		for i = 1:n
			x(i) = invdb(i) - invd(i).*(Moff(i,:)*x);
		end

		if norm( x - xprev, inf ) < e
			return;
		end
	end

	error 'the method did not converge';
end