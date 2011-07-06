function [ M, S ] = criaMatrizPrecisao( d, max )
%CRIAMATRIZ Generates the matrices of the problem's linear system
% d = internal points (real dimension is d+1)

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
  coef_precisao = 1/(12*h^2);

  %fprintf('dim = %d | max = %d | h = %d\n', dim, max, h);

  % Adiciona os coeficientes da equação em cada ponto
  row = 0;
  for y=1:dim
    for x=1:dim
      row = row + 1;
      fprintf('\nEquacao em T(%d, %d)\n', x, y);

      %Vai investigar os intervalos nessa ordem
      %[-2, 2]
      %[-1, 3]
      %[-3, 1]
      %[ 0, 4]
      %[-4, 0]
      x_equ_found = false;
      y_equ_found = false;
      for i=-2:0

        %Tenta o intervalo
        intf=i:i+4;

        if(~x_equ_found)
          x_equ_found = investigaIntervaloX(x, y, intf);
        end
        
        if(~y_equ_found)
          y_equ_found = investigaIntervaloY(x, y, intf);
        end

        %Tenta o intervalo contrario
        flip_intf=-fliplr(intf);
        if(all(intf == flip_intf))
          continue;
        else
          fprintf(' ** Inverteu \n');
          intf = flip_intf;
        end

        if(~x_equ_found)
          x_equ_found = investigaIntervaloX(x, y, intf);
        end

        if(~y_equ_found)
          y_equ_found = investigaIntervaloY(x, y, intf);
        end

        if(x_equ_found && y_equ_found)
%          M
%          S
%          exit();
          break;
        end

      end

      %fprintf('row %d\n', row);
    end
  end


  %tirar isso ajuda a debugar
% Nem precisa disso
%  M = M * coef_precisao;
%  S = S * coef_precisao;

  %size(M)
  %size(S)
end


function [is_valid_interval] = investigaIntervaloX(x, y, intf)
  global M S h dim row;

  intx=intf + ones(size(intf))*x;
  is_valid_interval = all(intx >= 0 ) && all( intx < dim+2 );

  if( is_valid_interval )
    fprintf(' - (x) intervalo aceito: [%d, %d]\n', intf(1), intf(end));
    switch(intf(1)+intf(end))
      case 0
        F3x(x, y)
      case 2
        F2x(x, y)
      case -2
        F4x(x, y)
      case 4
        F1x(x, y)
      case -4
        F5x(x, y)
    end
  end

end


function [is_valid_interval] = investigaIntervaloY(x, y, intf)
  global M S h dim row;

  inty=intf + ones(size(intf))*y;
  is_valid_interval = all(inty >= 0 ) && all( inty < dim+2 );

  if( is_valid_interval )
    fprintf(' - (y) intervalo aceito: [%d, %d]\n', intf(1), intf(end));
    switch(intf(1)+intf(end))
      case 0
        F3y(x, y)
      case 2
        F2y(x, y)
      case -2
        F4y(x, y)
      case 4
        F1y(x, y)
      case -4
        F5y(x, y)
    end
  end

end


function F1x(x, y)
  global M S h dim row;
  fprintf(' - F1 (%d, %d)\n', x, y);
  Fprecisao(x:x+4, y:y, [35 -104 114 -56 11])
end

function F1y(x, y)
  global M S h dim row;
  fprintf(' - F1\n');
  Fprecisao(x:x, y:y+4, [35 -104 114 -56 11])
end

function F2x(x, y)
  global M S h dim row;
  fprintf(' - F2\n');
  Fprecisao(x-1:x+3, y:y, [11 -20 6 4 -1])
end

function F2y(x, y)
  global M S h dim row;
  fprintf(' - F2\n');
  Fprecisao(x:x, y-1:y+3, [11 -20 6 4 -1])
end

function F3x(x, y)
  global M S h dim row;
  fprintf(' - F3\n');
  Fprecisao(x-2:x+2, y:y, [-1 16 -30 16 -1])
end

function F3y(x, y)
  global M S h dim row;
  fprintf(' - F3\n');
  Fprecisao(x:x, y-1:y+2, [-1 16 -30 16 -1])
end

function F4x(x, y)
  global M S h dim row;
  fprintf(' - F4\n');
  Fprecisao(x-3:x+1, y:y, [-1 4 6 -20 11])
end

function F4y(x, y)
  global M S h dim row;
  fprintf(' - F4\n');
  Fprecisao(x:x, y-3:y+1, [-1 4 6 -20 11])
end

function F5x(x, y)
  global M S h dim row;
  fprintf(' - F5\n');
  Fprecisao(x-4:x, y:y, [11 -56 114 -104 35])
end

function F5y(x, y)
  global M S h dim row;
  fprintf(' - F5\n');
  Fprecisao(x:x, y-4:y, [11 -56 114 -104 35])
end


function Fprecisao(intx, inty, coef)
  global M S h dim row;
%  global coef_precisao;
%  fprintf(' - Fprecisao %d \n', coef_precisao);

  ci = 1;
  for xi=intx
    for yi=inty
      %avaliaPonto(xi, yi, coef(ci) * coef_precisao);
      avaliaPonto(xi, yi, coef(ci));
      ci = ci + 1;
    end
  end
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

    fprintf(' [ T(%d, %d) = %d ] ', x, y, t);
    
  end


  function [ novo_coef ] = addCoef(row, x, y, coef)
    global M S h dim row;

    coluna = ((y-1) * dim) + x;
    novo_coef = M(row, coluna) + coef;
    M(row, coluna) = novo_coef;
    fprintf(' [ T(%d, %d) * %d ] ', x, y, coef);
  end
  

  function avaliaPonto(i, j, peso)
    global M S h dim row;
    fprintf(' - avalia T(%d, %d) %d', i, j, peso);

    %O ponto pode ser:
    %(1) Um ponto não interno (borda ou exterior)
    if (i <= 0 || j <= 0 || i > dim || j > dim)
      if(i == 0 || j == 0 || i == dim+1 || j == dim+1)
        %(A) Um ponto na borda
        %Entra sempre como valor

        point_value = (peso * -1) * T(i, j);
        fprintf(' coef => %d', point_value);
        S(row,1) = S(row,1) + point_value;
      else
        %(B) Um ponto exterior que foi rebatido para um interior
        fprintf(' - Um ponto externo??? Nao deveria existir esse caso\n');
        exit();
        %addCoef(row, ni, nj, peso);
      end

    %1) Um ponto interno
    else
      addCoef(row, i, j, peso);
    end
    
    fprintf('\n');

  end

