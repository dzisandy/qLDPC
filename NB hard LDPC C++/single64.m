fe = 20;
snr = 1:0.5:8.5;
addpath encoder;
addpath decoder;
addpath ./tools/conv/;
%simulate('H200x1000_R080_q4_reg9.alist', 7 , 10, snr, fe,[0])
%simulate('H133x667_R080_q8_reg9.alist', 7 , 10, snr, fe,[0])
%simulate('H100x500_R080_q16_reg9.alist', 7 , 10, snr, fe,[0])
%simulate('H80x400_R080_q32_reg9.alist', 7 , 10, snr, fe,[0])
simulate('H67x334_R080_q64_reg9.alist', 7 , 10, snr, fe,[0])
exit();