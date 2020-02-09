% Program for benchmarking of the official implementation of Reverse
% Cuthill McKee Algorithm and comparison with my own parallel
% implementation for the Course Parallel and Distributed Systems

n = 500;    %500, 1000, 5000, 10.000, 15.000 20.000
sparsity = 0.01;

% Initialize sparse matrix a with sparsity as defined above
A = zeros(n, n);
for i=1:n
    for j = 1:i-1
        r = rand(1);
        if r < sparsity
            A(i, j) = 1;
            A(j, i) = 1;
        else
            A(i, j) = 0;
            A(j, i) = 0;
        end
    end
    A(i, i) = 1;
end

tic
r = symrcm(A);
toc