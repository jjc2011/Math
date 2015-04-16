%
% BackwardEuler.m
%
function y = BackwardEuler(f,fy,a,b,N,y0)
%
% This function uses backward Euler to approximate the solution of the
% initial value problem
% 
%    y'(t) = f(t,y),  a <= t <= b
%    y(a) = y0.
%
% INPUTS:  f      A function of two variables f(t,y) returning the rhs of
%                 the ODE.
%          fy     A function of two variables fy(t,y) returning the partial
%                 derivative of f with respect to y.
%          a, b   The lower and upper bounds on t.
%          N      The number of intervals that the interval [a,b] is to be
%                 divided into.
%          y0     The initial condition.
%
% OUTPUTS: y      A vector of length (N+1) containing the computed values
%                 of y at each of the nodes t_i = a + i*h.
%

% The stepsize.
h = (b-a) / N;

% The initial time.
t = a;

% The initial condition.
y = y0;

% Tolerance to use in the Newton step.
tol = h^3;

% Maximum Newton iterations.
maxIts = 50;

% The backward Euler procedure.
for jj = 1:N,
    
    % Update the location for t.
    t = t + h;
    
    % The update at the next time satisfies this equation.
    F = @(ynew) ynew - h*f(t,ynew) - y(jj);
    
    % The derivative of this function.
    dF = @(ynew) 1 - h*fy(t,ynew);
    
    % Update y.
    y(jj+1) = Newton(F,dF,y(jj),tol,maxIts);
    exact(jj) = exp(-5*t) + exp(t);
    error(jj) = abs(exact(jj) - y(jj+1));
    
end;

disp(exact);
disp(error);