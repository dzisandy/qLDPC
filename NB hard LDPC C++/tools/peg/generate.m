% Generating matrices of size a x b over GF(q) with weights 3,5,7. Use for save_m.m in ./tools/conv
a = 200;
b = 1000;
q = 4;
H1 = peg(a, b, 3, 1);
H2 = peg(a, b, 5, 1);
H3 = peg(a, b, 7, 1);
H4 = peg(a, b, 9, 1);

H1(H1 > 0) = randi(q-1, 1, nnz(H1));
H2(H2 > 0) = randi(q-1, 1, nnz(H2));
H3(H3 > 0) = randi(q-1, 1, nnz(H3));
H4(H4 > 0) = randi(q-1, 1, nnz(H4));

