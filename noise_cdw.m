function [cwd] = noise_cdw(n,p,m)
q = 2^m;
cwd = zeros(1, n); 
ind = find(rand(1,n) < p); 
cwd(ind) = randi([1 q-1], 1, length(ind))
end