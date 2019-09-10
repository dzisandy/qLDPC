function ldgmMatListGenRecur(bmM, bmN, currHb, currWeight, fileNamePrefix)

currRestCols = bmN - size(currHb, 2) - bmM;

if currRestCols == 0
    fileNamePostfix = '';
    temp = sum(currHb, 1);
    for i = 1:bmM
        fileNamePostfix = [fileNamePostfix sprintf('_%d%d', i, sum(temp == i))];
    end
    fileName = [fileNamePrefix fileNamePostfix '.alist'];
    Hb = [currHb eye(bmM)];
    sparse2alist(2, Hb, fileName);
elseif currWeight == bmM
    for i = 1:currRestCols
        currCol = zeros(bmM, 1);
        currCol(1:currWeight) = 1;
        currCol = currCol(randperm(bmM));
        currHb = [currHb currCol];
    end
    fileNamePostfix = '';
    temp = sum(currHb, 1);
    for i = 1:bmM
        fileNamePostfix = [fileNamePostfix sprintf('_%d%d', i, sum(temp == i))];
    end
    fileName = [fileNamePrefix fileNamePostfix '.alist'];
    Hb = [currHb eye(bmM)];
    sparse2alist(2, Hb, fileName);
else
    for currWeightColNum = 0:currRestCols
        currHbPart = [];
        if currWeightColNum > 0
            for i = 1:currWeightColNum
                currCol = zeros(bmM, 1);
                currCol(1:currWeight) = 1;
                currCol = currCol(randperm(bmM));
                currHbPart = [currHbPart currCol];
            end
        end
        ldgmMatListGenRecur(bmM, bmN, [currHb currHbPart], currWeight+1, fileNamePrefix);
    end
end

end