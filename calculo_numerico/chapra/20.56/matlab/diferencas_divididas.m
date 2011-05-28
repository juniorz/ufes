% From: http://persson.berkeley.edu/128A/lec11-2x3.pdf
function F = diferencas_divididas( x, f )
  n=length(x)-1;
  F=zeros(n+1,n+1);
  F(:,1)=f(:);
  
  for i=1:n
    for j=1:i
      F(i+1,j+1)=(F(i+1,j)-F(i,j))/(x(i+1)-x(i-j+1));
    end
  end
  
end
