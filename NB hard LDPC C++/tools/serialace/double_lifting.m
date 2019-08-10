function [Hpar,M1] = double_lifting(Hbase,Z,depth)
addpath ../conv/
Z1=max(max(Hbase))+1;
[mb,nb]=size(Hbase);
M1=zeros(mb*Z1,nb*Z1);
for i=1:mb
    for j=1:nb
        if Hbase(i,j)>0
            pi=randperm(Z1);
            g=zeros(1,Z1);
            g(pi(1:Hbase(i,j)))=1;
            Mh=[];
            for s=0:Z1-1
                Mh=[Mh; circshift(g,[0, s])];
            end;
            M1(1+Z1*(i-1):Z1*i,1+Z1*(j-1):Z1*j)=Mh;
        end;
    end;
end;
[H_exp, H_q] = make_ldpc_ace3(2, Z, M1, depth);
Hpar = exp2sparse(2, Z, H_exp, H_q);
end

