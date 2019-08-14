a = 80;
b = 400;
q = 32;
H1 = peg(a, b, 3, 1);
H2 = peg(a, b, 5, 1);
H3 = peg(a, b, 7, 1);
H1(H1 > 0) = randi(q-1, 1, nnz(H1));
H2(H2 > 0) = randi(q-1, 1, nnz(H2));
H3(H3 > 0) = randi(q-1, 1, nnz(H3));

