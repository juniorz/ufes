%/*****************************************************************************
% * 20.56 Solution
% * Numerical Methods for Engineers, Chapra, 5th Ed.
% *****************************************************************************
% * © Copyright 2011 Reinaldo de Souza Junior. Some Rights Reserved.
% * This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 License
% * More info: http://creativecommons.org/licenses/by-nc-sa/3.0/
% *****************************************************************************/
 
function Fi = interpolacao_dif_div(x, X, Fx )

  Fi = 0;
  prod_difer = 1;

  for i=1:size(Fx,1)
    Fi = Fi + prod_difer * Fx(i);
    prod_difer = prod_difer * (x - X(i));
  end

end

