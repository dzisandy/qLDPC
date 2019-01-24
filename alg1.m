function [c,F] = alg1(r, m, H, theta)
[~,N] = size(H);
H_gf = gf(full(H.'),m);
S = gf(r,m)*H_gf;
b = 1;
while b == 1
    b = 0;
    for i = 1:N
        j = find(H(:,i));
        msg = gf(full(H(j,i)),m).^-1;
        k = msg.' .* S(j);
        k = k.x;
        [~,l] = size(k);
        z = l - nnz(k);
        y = zeros(size(k));
        for p = 1:length(k)
            if k(p) ~= 0
                y(p) = sum(k==k(p));
            else 
                y(p) = 0;
            end
        end
        [a, argmax] = max(y);
        M = k(argmax);
        if a - z >= theta
            final = gf(r(i),m) + gf(M, m);
            r(i) = final.x;
            S = gf(r,m)*H_gf;
            b = 1;
        end
    end
    F = 1;
    c = r;
    if nnz(S.x) == 0
        F = 0;
    end

      
    end

            
            
    
end
