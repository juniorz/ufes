% Essas são as equações resultantes do problema aplicado para 5x5 pontos
% internos.

% Para a geração da matrix, apenas as equações relativas aos pontos
% internos serão usadas, ou seja, não será usada nenhuma equação na forma:
% T(x0,y0) = ... , com x0 = 0 ou y0 = 0

% T(0,0) = 1/4 * ( 2 * T(1,0) + 2 * T(0,1) )
% T(0,1) = 1/4 * ( 2 * T(1,1) + T(0,0) + T(0,2) )
% T(0,2) = 1/4 * ( 2 * T(1,2) + T(0,1) + T(0,3) )
% T(0,3) = 1/4 * ( 2 * T(1,3) + T(0,2) + T(0,4) )
% T(0,4) = 1/4 * ( 2 * T(1,4) + T(0,3) + T(0,5) )
% T(0,5) = 1/4 * ( 2 * T(1,5) + T(0,4) + T(0,6) )
% T(0,6) = 1/4 * ( 2 * T(1,6) + 2 * T(0,5) )

% T(1,0) = 1/4 * ( T(0,0) + T(2,0) + 2 * T(1,1) ) %não usa
% T(1,1) = 1/4 * ( T(0,1) + T(2,1) + T(1,0) + T(1,2) )
% T(1,2) = 1/4 * ( T(0,2) + T(2,2) + T(1,1) + T(1,3) )
% T(1,3) = 1/4 * ( T(0,3) + T(2,3) + T(1,2) + T(1,4) )
% T(1,4) = 1/4 * ( T(0,4) + T(2,4) + T(1,3) + T(1,5) )
% T(1,5) = 1/4 * ( T(0,5) + T(2,5) + T(1,4) + T(1,6) )
% T(1,6) = 1/4 * ( T(0,6) + T(2,6) + 2 * T(1,5) )
% 
% T(2,0) = 1/4 * ( T(1,0) + T(3,0) +      2 * T(2,1) )
% T(2,1) = 1/4 * ( T(1,1) + T(3,1) + T(2,0) + T(2,2) )
% T(2,2) = 1/4 * ( T(1,2) + T(3,2) + T(2,1) + T(2,3) )
% T(2,3) = 1/4 * ( T(1,3) + T(3,3) + T(2,2) + T(2,4) )
% T(2,4) = 1/4 * ( T(1,4) + T(3,4) + T(2,3) + T(2,5) )
% T(2,5) = 1/4 * ( T(1,5) + T(3,5) + T(2,4) + T(2,6) )
% T(2,6) = 1/4 * ( T(1,6) + T(3,6) +      2 * T(2,5) )
% 
% T(3,0) = 1/4 * ( T(2,0) + T(4,0) +      2 * T(3,1) )
% T(3,1) = 1/4 * ( T(2,1) + T(4,1) + T(3,0) + T(3,2) )
% T(3,2) = 1/4 * ( T(2,2) + T(4,2) + T(3,1) + T(3,3) )
% T(3,3) = 1/4 * ( T(2,3) + T(4,3) + T(3,2) + T(3,4) )
% T(3,4) = 1/4 * ( T(2,4) + T(4,4) + T(3,3) + T(3,5) )
% T(3,5) = 1/4 * ( T(2,5) + T(4,5) + T(3,4) + T(3,6) )
% T(3,6) = 1/4 * ( T(2,6) + T(4,6) +      2 * T(3,5) )
% 
% 
% T(4,0) = 1/4 * ( T(3,0) + T(5,0) +      2 * T(4,1) )
% T(4,1) = 1/4 * ( T(3,1) + T(5,1) + T(4,0) + T(4,2) )
% T(4,2) = 1/4 * ( T(3,2) + T(5,2) + T(4,1) + T(4,3) )
% T(4,3) = 1/4 * ( T(3,3) + T(5,3) + T(4,2) + T(4,4) )
% T(4,4) = 1/4 * ( T(3,4) + T(5,4) + T(4,3) + T(4,5) )
% T(4,5) = 1/4 * ( T(3,5) + T(5,5) + T(4,4) + T(4,6) )
% T(4,6) = 1/4 * ( T(3,6) + T(5,6) +      2 * T(4,5) )
% 
% T(5,0) = 1/4 * ( T(4,0) + T(5,0) +      2 * T(5,1) )
% T(5,1) = 1/4 * ( T(4,1) + T(5,1) + T(5,0) + T(5,2) )
% T(5,2) = 1/4 * ( T(4,2) + T(5,2) + T(5,1) + T(5,3) )
% T(5,3) = 1/4 * ( T(4,3) + T(5,3) + T(5,2) + T(5,4) )
% T(5,4) = 1/4 * ( T(4,4) + T(5,4) + T(5,3) + T(5,5) )
% T(5,5) = 1/4 * ( T(4,5) + T(5,5) + T(5,4) + T(5,6) )
% T(5,6) = 1/4 * ( T(4,6) + T(5,6) +      2 * T(5,5) )
% 
% T(6,0) = 1/4 * ( 2 * T(6,1) +      2 * T(5,0) )
% T(6,1) = 1/4 * ( T(6,1) + T(6,0) + 2 * T(5,1) )
% T(6,2) = 1/4 * ( T(6,2) + T(6,1) + 2 * T(5,2) )
% T(6,3) = 1/4 * ( T(6,3) + T(6,2) + 2 * T(5,3) )
% T(6,4) = 1/4 * ( T(6,4) + T(6,3) + 2 * T(5,4) )
% T(6,5) = 1/4 * ( T(6,5) + T(6,4) + 2 * T(5,5) )
% T(6,6) = 1/4 * ( 2 * T(6,5) +      2 * T(5,6) )

function [ M, S ] = criaMatriz( dim, max )
%CRIAMATRIZ Summary of this function goes here
%   Detailed explanation goes here

  global M S h;

  h = max / (dim+1);
  M = zeros(dim^2); %T(1,1), T(2,1), ... , T(4,5), T(5,5)
  S = zeros(dim^2, 1);

  %fprintf('dim = %d | max = %d | h = %d\n', dim, max, h);
  
%   %Vou Usar:
% 
% 
%   % T(1,4) = 1/4 * ( T(0,4) + T(2,4) + T(1,3) + T(1,5) )
%   % T(1,5) = 1/4 * ( T(0,5) + T(2,5) + T(1,4) + T(1,6) )
% 
%   %1:
%   % T(1,1) = 1/4 * ( T(0,1) + T(2,1) + T(1,0) + T(1,2) )
%   % T(1,1) - 1/4 * (T(2,1) + T(1,2)) = 1/4 * (T(0,1) + T(1,0))
%   row = row + 1;
%   addCoef(row, 1, 1, 1);
%   addCoef(row, 1, 2, -1/4);
%   addCoef(row, 2, 1, -1/4);
%   S(row,1) = 1/4 * (T(0,1) + T(1,0));
%   
%   
%   %2:
%   % T(1,2) = 1/4 * ( T(0,2) + T(2,2) + T(1,1) + T(1,3) )
%   % T(1,2) - 1/4( T(2,2) + T(1,1) + T(1,3) ) = 1/4 * T(0,2)
%   row = row + 1;
%   addCoef(row, 1, 1, -1/4);
%   addCoef(row, 1, 2, 1);
%   addCoef(row, 1, 3, -1/4);
%   addCoef(row, 2, 2, -1/4);
%   S(row,1) = 1/4 * (T(0,2));
% 
%   
%   %3:
%   % T(1,3) = 1/4 * ( T(0,3) + T(2,3) + T(1,2) + T(1,4) )
%   % T(1,3) = 1/4 * ( T(0,3) + T(2,3) + T(1,2) + T(1,4) )
% %   row = row + 1;
% %   addCoef(row, 1, 1, -1/4);
% %   addCoef(row, 1, 2, 1);
% %   addCoef(row, 1, 3, -1/4);
% %   addCoef(row, 2, 2, -1/4);
% %   S(row,1) = 1/4 * (T(0,2));


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

  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  function [ t ] = T(x, y)
    t = NaN;
    
    if x == 0 || y == dim+1
      t = 0;
    elseif y == 0 || x == dim+1      
      t = x * h - y * h;
    end

%    fprintf(' [ T(%d, %d) = %d ] ', x, y, t);
    
  end


  function [ novo_coef ] = addCoef(row, x, y, coef)
    coluna = (y-1) * dim + (x-1) + 1;
    novo_coef = M(row, coluna) + coef;
    M(row, coluna) = novo_coef;
    
%    fprintf(' [ T(%d, %d) * %d ] ', x, y, coef);
    
  end
  

  function avaliaPonto(i, j, peso)
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

end

