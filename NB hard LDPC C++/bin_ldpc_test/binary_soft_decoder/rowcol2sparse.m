function H_sparse = rowcol2sparse(H_rows, H_cols)
    H_n  = size(H_cols, 2);
    H_m = size(H_rows, 1);
    H_sparse = zeros(H_m, H_n);
    for i = 1:H_n
        H_sparse(H_cols(H_cols(:, i) ~= 0, i), i) = 1;
    end
    H_sparse = sparse(H_sparse);
end
