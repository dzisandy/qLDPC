[H,Q] = alist2sparse('test.alist'); %parity check matrix in sparse format
[M,N] = size(H); % defining sizes
m  = 9; % gf(2^m)
fid = fopen('FER_2.txt', 'w');
p = 0.03;
%H = full(H);
%r = noise_cdw(N,p,m); 
thetas = 1:54
%alg2(r, m, H, thetas)
for j = [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20]
    fer = 0;
    er = 0;
    for i = 1:500
        disp(i)
        r = noise_cdw(N,j,m);
        [c,~] = alg2(r, m, H, thetas);
        if c == zeros(1, N)
            er = er + 1;
        end
    end
    disp(j)
    fer = (500-er)/500
    fprintf(fid,'%d\n', fer); 
end
%max weight of H row is 54 
%
% proof
%
%for i = 1:N
%    z(i) = sum(H(:,i) )
%end
%max(z)