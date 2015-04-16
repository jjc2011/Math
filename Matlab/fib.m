function p = Fibonacci(n)
%
% Fibonacci.m
%
% This function computes the first n Fibonacci terms p_n defined by the
% recursive equation
% 
% p_n = p_{n-1} + p_{n-2}
% 
% starting from the given values of p_0 and p_1.
%
% INPUTS:  n        The number of terms 
%
% OUTPUTS: p        A vector of length (n+1) that stores all the terms p_n
%

% Create a vector to store the results.
p = zeros(1,n+1);

% The initial values.
p(1) = 1;
p(2) = 1;

% Recursively compute the new terms from p_2 to p_n.
for jj = 2:n
    
    % Compute the newest term p_j.
    p(jj+1) = p(jj) + p(jj-1);
    
end;