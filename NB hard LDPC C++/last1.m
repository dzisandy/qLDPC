
addpath encoder;
addpath decoder;
addpath ./tools/conv/;
%simulate('H200x1000_R080_q4_reg9.alist', 7, 10,1:0.5:8.5, 20, [8,7,6,5,4,3,2,1,0])
%simulate('H67x334_R080_q64_reg7.alist', 7, 10,1:0.5:8.5, 20, [6,5,4,3,2,1,0])
%simulate('H133x667_R080_q8_reg9.alist', 7, 10,1:0.5:8.5, 20, [8,7,6,5,4,3,2,1,0])
exit();