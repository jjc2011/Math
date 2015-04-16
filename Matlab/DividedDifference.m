%
% DividedDifference.m.
%
function coeff = DividedDifference(x,f,n)
%
% This function uses divided differences to compute the coefficients of an
% interpolating polynomial of the form
% p(x) = c0 + c1(x-x_0) + c2(x-x_0)(x-x_1) + ... + cn(x-x_0)...(x-x_{n-1})
% The coefficient cj is given by the jth divided difference f[x_0,...,x_j].
%
% INPUTS:  x     A vector containing the nodes where the data is given.
%          f     A vector the same length as x giving the function values
%                at the nodes.
%          n     The order of the interpolating polynomial.
%
% OUPUTS:  coeff A vector the same length as x containing the coefficients.
%

% The zeroth divided differences are simply the function values.
coeff = f;

% Successively compute the higher divided differences.
% At each step we rewrite the lower divided differences that will not show
% up as coefficients in the interpolating polynomial.
for jj = 2:n+1
    
    coeff(jj:end) = (coeff(jj:end) - coeff(jj-1:end-1)) ./ ...
        (x(jj:end) - x(1:n-jj+2));
    
end;