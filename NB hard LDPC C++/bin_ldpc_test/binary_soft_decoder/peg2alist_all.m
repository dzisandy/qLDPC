function peg2alist_all(q, template)
    mat_comma = dir(template);
    mat_list = {mat_comma.name};

    for file = mat_list
        peg2alist(char(file), q, 1);
    end
end