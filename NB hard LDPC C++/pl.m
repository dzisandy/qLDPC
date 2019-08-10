% plotiing functions, for data, refer to test.m
matrix = 'H500x100_R080_q16_reg3.alist';
error = 'FER 3';
load(sprintf('result_q=16_ldpc=%s_decoder=5_iter=10.mat', matrix))
semilogy(snr_array, fer, '-r')
grid on
hold on
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=3.mat', matrix))
semilogy(snr_array, fer, '-b')
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=2.mat', matrix))
semilogy(snr_array, fer, '-p')
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat', matrix))
semilogy(snr_array, fer, '-g')
load(sprintf('result_q=16_ldpc=%s_decoder=6_iter=10.mat', matrix))
semilogy(snr_array, fer, '-c')
%load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=5.mat', matrix))
%semilogy(snr_array, ser, '-m')
hold off
legend(sprintf('%s Majority ', error),sprintf('%s Treshold 3', error),sprintf('%s Treshold 2', error), sprintf('%s Treshold 1', error), sprintf('%s MajoritySeq', error))