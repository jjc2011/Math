%
% Euler.m
%
function y = Euler(f,a,b,N,y0)
%
% This function uses Euler's method to approximate the solution of the
% initial value problem
%
% y'(t) = f(t,y), a <= t <= b
% y(a) = y0.
%
% INPUTS: f A function of two variables f(t,y) returning the rhs of
% the ODE.
% a, b The lower and upper bounds on t.
% N The number of intervals that the interval [a,b] is to be
% divided into.
% y0 The initial condition.
%
% OUTPUTS: y A vector of length (N+1) containing the computed values
% of y at each of the nodes t i = a + i*h.
%
% The stepsize.
h = (b-a) / N;
% The initial time.
t = a;
% The initial condition.
y = y0;

% The Euler procedure.
for jj = 1:N,

    % The update at the next time.
    y(jj+1) = y(jj) + h * f(t,y(jj));
    % Update the location for t.
    t = t + h;
    exact(jj) = exp(-5*t) + exp(t);
    exact(jj) = abs(exact(jj) - y(jj+1));
    
end;

disp(exact);