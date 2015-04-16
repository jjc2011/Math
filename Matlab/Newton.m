%
% Newton.m.
%
function x = Newton(f,df,x0,tol,maxIts)
%
% This function uses Newton's method to solve the scalar equation
% f(x) = 0.
%
% INPUTS: f A function handle defining the function f(x).
% df A function handle defining the derivative f'(x).
% x0 An initial guess.
% tol The error tolerance.
% maxIts The maximum number of iterations.
%
% OUTPUTS: x The computed solution.
%
% The iteration counter.
its = 0;
% The change in the update, which is initially undefined.
diffX = inf;
% Iterate.
while (diffX>tol && its<maxIts)
% Count this iteration.
its = its + 1;
% Update.
x = x0 - f(x0) / df(x0);
% The change in x.
diffX = abs(x-x0);
% Store the current solution value.
x0 = x;
end;
% Did we succeed?
if diffX>tol
warning('Maximum number of iterations reached.');
end;
