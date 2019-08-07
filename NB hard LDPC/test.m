fe = 100;
snr = [1:0.5:8.5];
for i=5:7
    simulate('test.alist', i, 10, snr, fe, [0]);
end
simulate('test.alist', i, 10, snr, fe, [2,1,0]);
simulate('test.alist', i, 10, snr, fe, [4,3,2,1,0]);