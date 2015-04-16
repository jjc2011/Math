%
% Eval.m.
%
function result = Eval(n,c,x,p)
%
% This function calculates a polynomial
% p(x) = c0 + c1(x-x_0) + c2(x-x_0)(x-x_1) + ... + cn(x-x_0)...(x-x_{n-1})
%
% INPUTS:  n     The degree of the polynomial.
%          c     A vector containing the coefficients of the poly
%          x     A vector containing the locations of the nodes
%          p     A vector containing all the points to be evaluated
%
% OUPUTS:  result     A vector of the evaluations to the poly at values in x
%
% 3.3 #18a result =  1.0e+005 * [1.0240    2.1504    5.1344]
% 1940 -> 102400
% 1975 -> 215040
% 2020 -> 513440

%Loop over each point
    for index=1:length(p)    

%Calculate the differences
for jj = 1:n-1    
    d(jj) = p(index) - x(jj);
end;

%Add the first coeff
result(index) = c(1);

%Add the rest of the polynomial
for jj = 2:n
    result(index) = result(index) + c(jj)*prod(d(1:jj-1));
end;

end;