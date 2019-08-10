function H = peg2sparse(file_name, factor)
    file = fopen(file_name, 'r');
    
    % N M [Q]
    n = fscanf(file, '%d', 1);
    m = fscanf(file, '%d', 1);
    max_row = fscanf(file, '%d', 1);
    
    % read the graph
    Hb = sparse(m, n);
    for ii = 1:m
        indexes = fscanf(file, '%d', max_row)';
        nz_indexes = indexes(find(indexes));
        Hb(ii, nz_indexes) = 1;
    end
    
    fclose(file);

    %expand graph
    if factor > 1
        H = [];
        init_matrix = sparse(eye(factor));
        for ii = 1:m
            layer = [];
            for jj = 1:n
                shift = randi(factor) - 1;
                temp = circshift(init_matrix, -shift);
                layer = [layer Hb(ii, jj)*temp];
            end
            H = [H; layer];
        end
    else
        H = Hb;
    end
end
