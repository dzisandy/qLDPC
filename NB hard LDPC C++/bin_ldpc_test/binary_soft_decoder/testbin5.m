addpath ../../encoder;
addpath ../../tools/conv/;
simulate_bin('H400x2000_R080_q2_reg5.alist', 9, 10,1:0.5:8.5, 20, [0])
simulate_bin('H400x2000_R080_q2_reg5.alist', 9, 10,1:0.5:8.5, 20, [4,3,2,1,0])
exit();