function Hb = sparse2basemat( H, Mb, Nb, factor )

Hb = -1*ones(Mb, Nb);
for i = 1:Mb
    for j =1:Nb
        currRow = H(factor*(i-1)+1, (factor*(j-1)+1):(factor*j));
        if (any(currRow))
            Hb(i,j) = find(currRow) - 1;
        end
    end
end

end

