[H,Q] = alist2sparse('test.alist') %parity check matrix in sparse format
[M,N] = size(H); % defining sizes
r = zeros(1,N) %received sequince
r(16) = 1
r(17) = 2
r(1) = 1
r(2) = 1
m  = 9; % gf(2^m)
theta = 0; %threshold
alg1(r, m, H, theta) % algorithm 1