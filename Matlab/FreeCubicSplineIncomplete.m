%
% FreeCubicSplineIncomplete.m
%
function [a,b,c,d,S] = FreeCubicSplineIncomplete(n,x,f,y)
%
% This function is intended to compute the values of a free cubic spline 
% that interpolates the data (x_j, f_j).  In the inteveral [x_j,x_{j+1}], 
% j = 0,..,n-1, the spline is given by
% S_j(x) = a_j + b_j(x-x_j) + c_j(x-x_j)^2 + d_j(x-x_j)^3.
% 
% However, the code for computing the zeroth, first, and third order
% coefficients (a, b, d) is missing.
% The code for computing the second-order coefficients is copmlete.  The
% code for evaluating the spline is also complete.
%
% INPUTS:  n     The number of intervals used in the spline.
%          x     A vector of length (n+1) listing the nodes, which must be
%                unique and given in increasing order.
%          f     A vector of length (n+1) listing the function values at
%                the nodes.
%          y     A vector of points satisfying x_0 < y < x_n where the
%                spline is to be evaluated.  This can be simply an empty
%                vector.
%
% OUTPUTS: a     A vector of length n listing the zeroth-order
%                coefficients of the cubic polynomials.
%          b     A vector of length n listing the first-order
%                coefficients of the cubic polynomials.
%          c     A vector of length n listing the second-order
%                coefficients of the cubic polynomials.
%          d     A vector of length n listing the third-order
%                coefficients of the cubic polynomials.
%          S     A vector the same length as y giving the values of S(y).
%

% Make the inputs column vectors.
x = x(:);
f = f(:);

% Something is missing here. 
% Sets a as f(j)
for jj = 1:n+1
    a = f(jj);
end;
% The spacing of the nodes.
h = x(2:end) - x(1:end-1);

% Setup the linear system used to solve for c, the third-order
% coefficients.
% These are the lower, main, and upper diagonals of the matrix.
d1 = [h(1:end-1);0;0];
d2 = [1;2*(h(1:end-1)+h(2:end));1];
d3 = [0;0;h(2:end)];

% Solve the system A * c = rhs
A = spdiags([d1,d2,d3],-1:1,n+1,n+1);
rhs = [0;...
    3./h(1:end-1).*a(1:end-2) + 3./h(2:end).*a(3:end) - ...
    (3./h(1:end-1)+3./h(2:end)).*a(2:end-1);...0];
c = A\rhs;

%
% Something is missing here.
% Solve for b and d
for jj = 1:size(b)
    
    b(jj) = ((a(jj+1) - a(jj)) / h(jj)) - ((h(jj)*(c(jj+1) + 2*c(jj))) / 3);
    d(jj) = (c(jj+1) - c(jj)) / (3*h(jj));
    
end;
    
% Remove extra values a_n, c_n.
a(end) = [];
c(end) = [];

% Now we want to evaluate the spline S(y).
% First create the vector that will hold these values.
if nargin < 4
    y = [];
end;
S = zeros(size(y));

% Now loop through each value that needs to be evaluated.
for jj = 1:length(y)
    
    % Determine which interval this value of y is in.
    loc = find(and(y(jj)>=x(1:end-1),y(jj)<=x(2:end)),1);
    
    % Evaluate the cubic polynomial.
    S(jj) = a(loc) + b(loc)*(y(jj)-x(loc)) + ...
        c(loc)*(y(jj)-x(loc))^2 + d(loc)*(y(jj)-x(loc))^3;
    
end;