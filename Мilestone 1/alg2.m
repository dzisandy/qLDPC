function [c,F] = alg2(r,m, H, thetas)
[~,t] = size(thetas); 
H_gf = gf(full(H.'),m);
S = gf(r,m)*H_gf;
for i = 1:t
    [r,~] = alg1(r, m, H, thetas(i));
end
F = 1;
c = r;
if nnz(S.x) == 0
    F = 0;
end

end