matrix3 = 'H500x100_R080_q16_reg3.alist';
matrix5 = 'H500x100_R080_q16_reg5.alist';
error3 = 'SER 3';
error5 = 'SER 5';
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=3.mat', matrix3))
semilogy(snr_array, ser, '-r')
grid on
hold on
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=5.mat', matrix5))
semilogy(snr_array, ser, '-g')
hold off
legend(sprintf('%s best (Treshold 3) ', error3),sprintf('%s best (Treshold 5)', error5))