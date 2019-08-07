load('result_q=16_ldpc=test.alist_decoder=5_iter=10.mat')
semilogy(snr_array, fer, '-r')
grid on
hold on
load('result_q=16_ldpc=test.alist_decoder=7_iter=10_thetas_num=5.mat')
semilogy(snr_array, fer, '-b')
load('result_q=16_ldpc=test.alist_decoder=7_iter=10_thetas_num=3.mat')
semilogy(snr_array, fer, '-p')
load('result_q=16_ldpc=test.alist_decoder=7_iter=10_thetas_num=1.mat')
semilogy(snr_array, fer, '-g')
load('result_q=16_ldpc=test.alist_decoder=6_iter=10.mat')
semilogy(snr_array, fer, '-k')
hold off
legend('Majority','Threshold 5', 'Threshold 3', 'Treshold 1', 'MajoritySeq')