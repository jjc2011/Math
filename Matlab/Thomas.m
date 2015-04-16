%
% Thomas.m
%
function y = Thomas(x,d,N)
%
% This function uses Thomas algorithm to solve a linear system
%
% INPUTS:  x      A 2D vector, NxN that is the linear system to solve
%          d      The RHS of the linear system
%          N      The length of the linear system
%          
% OUTPUTS: y      A 1xN vector with the values to 
%
% EXAMPLE: x1 =  0, x2 = 10, x3 = 20, x4 = 30, x5 = 40, x6 = 50, 
%          x7 = 60, x8 = 70, x9 = 80, x10 = 90, x11 = 100
    
% Set up helper vectors
for ii = 1:N-1,
    b(ii) = x(ii,ii);
    a(ii+1) = x(ii+1,ii);
    c(ii) = x(ii,ii+1);
end;
b(N) = x(N,N);
c(1) = c(1) / b(1);
d(1) = d(1) / b(1);
% Change coefficients
for ii = 2:N-1, 
    c(ii) = c(ii) / (b(ii) - a(ii)*c(ii-1));
    d(ii) = (d(ii) - a(ii)*d(ii-1))/(b(ii) - a(ii)*c(ii-1));
end;   
d(N) = (d(N) - a(N)*d(N-1))/(b(N) - a(N)*c(N-1));

% Solve using back substitution
y(N) = d(N);
for ii = 1:N-1,
    y(N-ii) = d(N-ii) - c(N-ii)*y(N-ii+1);
end;
