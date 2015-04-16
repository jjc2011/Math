%
% Bisection.m
%
function p = Bisection(f,a,b,tol)
%
% This function uses the bisection algorithm to find a root p of the
% nonlinear equation
% f(x) = 0
% The computed root has an error less than the given tolerance.
% The algorithm starts from values a, b such that f(a) and f(b) have
% opposite signs.
%
% INPUTS:  f      A function that returns f(x)
%          a,b    Endpoints of the interval.  These must satisfy 
%                 f(a) * f(b) <= 0 or the algorithm will fail.
%          tol    Error tolerance.
%
% OUTPUTS: p      The computed root.
%

% Evaluate the function at the endpoints.
fa = f(a);
fb = f(b);

% Make sure the function has opposite signs at the endpoints.
if fa * fb > 0
    warning('f(a) and f(b) must have opposite signs.');
    p = [];
    return;
end;

% Perform the bisection algorithm until the desired tolerance is attained.
while abs(a-b)/2 > tol
    
    % Find the midpoint of the interval.
    p = 0.5 * (a + b);
    
    % The function value at the midpoint.
    fp = f(p);
    
    % Adjust the interval.
    if fa * fp <= 0
        b = p;
    else
        a = p;
        fa = fp;
    end;
    
end;

% Compute the midpoint, which is the final approximation of the root.
p = 0.5 * (a + b);