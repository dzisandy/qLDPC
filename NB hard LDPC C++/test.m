%running the  simulation, creating files for plotting
fe = 20;
matrix = 'H500x100_R080_q16_reg5.alist';
snr = [1:0.5:8.5];
for i=5:7
    simulate(matrix, i, 10, snr, fe, [0]);
end
simulate(matrix, i, 10, snr, fe, [1,0]);
simulate(matrix, i, 10, snr, fe, [2,1,0]);