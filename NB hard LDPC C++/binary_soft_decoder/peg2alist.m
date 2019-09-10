function peg2alist(file_name, q, factor)
    H2 = peg2sparse(file_name, factor);
    Hq = convert_to_nonbinary(q, H2); 
    [PATHSTR,name,EXT] = fileparts(file_name);
    sparse2alist(q, Hq, strcat(name, '.alist'));
end
