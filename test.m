[H,Q] = alist2sparse('test.alist') %parity check matrix in sparse format
[M,N] = size(H); % defining sizes
m  = 9; % gf(2^m)
p = 0.01; %error probability
r = noise_cdw(N,p,m)%received sequince
theta = 0; %threshold
alg1(r, m, H, theta) % algorithm 1