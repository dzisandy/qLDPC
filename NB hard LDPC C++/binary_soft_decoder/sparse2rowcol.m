function [H_rows, H_cols] = sparse2rowcol(H)
    [M, N] = size(H);
    max_col = max(sum(H,1));
    max_row = max(sum(H,2));
        
    H_rows = [];
    for i = 1:M
        temp = find(H(i,:))';
        temp = [temp; zeros(max_row - length(temp), 1)];
        H_rows = [H_rows temp];
    end
    H_rows = H_rows';
    
    H_cols = [];
    for j = 1:N
        temp = find(H(:,j));
        temp = [temp; zeros(max_col - length(temp), 1)];
        H_cols = [H_cols temp];
    end
    
end