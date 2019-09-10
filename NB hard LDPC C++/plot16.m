matrix = 'H100x500_R080_q16_reg3.alist';
load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=3.mat', matrix));
semilogy(snr_array, fer,'LineWidth',2)
grid on
hold on
for i = [5,7,9]
    matrix = sprintf('H100x500_R080_q16_reg%i.alist',i);
    load(sprintf('result_q=16_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat', matrix, i));
    semilogy(snr_array, fer,'LineWidth',2)
end
title('Comparison of weight best for Q = 16')
legend({'weight = 3','weight = 5','weight = 7','weight = 9' },'Location', 'southwest')
saveas(gcf,sprintf('Best_Q=16.png', qq, weight))
