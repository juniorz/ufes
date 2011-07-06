function [ M, S ] = criaMatriz( d, max )
%CRIAMATRIZ Generates the matrices of the problem's linear system

%/*****************************************************************************
% * P29.7
% * Solution using LU decomposition and Gauss-Seidel methods.
% * Numerical Methods for Engineers, Chapra, 5th Ed.
% *****************************************************************************
% * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
% * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
% * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
% *****************************************************************************/

  global M S h dim row;

  dim = d;
  h = max / (dim+1);
  M = zeros(dim^2); %T(1,1), T(2,1), ... , T(4,5), T(5,5)
  S = zeros(dim^2, 1);

  %fprintf('dim = %d | max = %d | h = %d\n', dim, max, h);
  
  % Adiciona os coeficientes da equação em cada ponto
  row = 0;
  for y=1:dim
    for x=1:dim
      row = row + 1;
%      fprintf('\nEquação em T(%d, %d)\n', x, y);

      avaliaPonto(x, y, 1);       %Centro
      avaliaPonto(x, y+1, -1/4);  %Norte
      avaliaPonto(x, y-1, -1/4);  %Sul
      avaliaPonto(x+1, y, -1/4);  %Leste
      avaliaPonto(x-1, y, -1/4);  %Oeste

      %fprintf('row %d\n', row);
    end
  end
    
  
  
  %size(M)
  %size(S)
end


  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  function [ t ] = T(x, y)
    global M S h dim row;
  
    t = NaN;
    
    if x == 0 || y == dim+1
      t = 0;
    elseif y == 0 || x == dim+1      
      t = x * h - y * h;
    end

%    fprintf(' [ T(%d, %d) = %d ] ', x, y, t);
    
  end


  function [ novo_coef ] = addCoef(row, x, y, coef)
    global M S h dim row;
  
    coluna = (y-1) * dim + (x-1) + 1;
    novo_coef = M(row, coluna) + coef;
    M(row, coluna) = novo_coef;
    
%    fprintf(' [ T(%d, %d) * %d ] ', x, y, coef);
    
  end
  

  function avaliaPonto(i, j, peso)
    global M S h dim row;
%    fprintf(' - avalia T(%d, %d)', i, j);

    %O ponto pode ser:
    %(1) Um ponto não interno (borda ou exterior)
    if (i <= 0 || j <= 0 || i > dim || j > dim)

      % Se for exterior tem que ser rebatido pra algum ponto dentro ;)
      % Daí vai sair o 2* T(a,b)
      if(i == 0)
        ni = i;
      elseif(i < 0)
        ni = abs(i);
      else
        ni = 2 * (dim + 1) - i;
      end

      if(j == 0)
        nj = j;
      elseif(j < 0)
        nj = abs(j);
      else
        nj = 2 * (dim + 1) - j;
      end

      if(i == 0 || j == 0 || i == dim+1 || j == dim+1)
        %(A) Um ponto na borda
        %Entra sempre como valor

        point_value = (peso * -1) * T(i, j);
        S(row,1) = S(row,1) + point_value;
      else
        %(B) Um ponto exterior que foi rebatido para um interior
        %Entra sempre como coeficiente
        addCoef(row, ni, nj, peso);
      end

    %1) Um ponto interno
    else
      addCoef(row, i, j, peso);
    end
    
%    fprintf('\n');

  end

