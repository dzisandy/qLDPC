%Used for plotting the results, taken from test_.m. Set Q and column
%weight.
qq = 64; % Q = 2/4/8/16/32/64 
weight = 5;  % w_c = 3/5/7
if (qq == 2)
    matrix = sprintf('H400x2000_R080_q%i_reg%i.alist',qq, weight);
elseif (qq == 4)
    matrix = sprintf('H200x1000_R080_q%i_reg%i.alist',qq, weight);
elseif (qq == 8)
    matrix = sprintf('H133x667_R080_q%i_reg%i.alist',qq, weight);
elseif (qq == 16)
    matrix = sprintf('H100x500_R080_q%i_reg%i.alist',qq, weight);
elseif (qq == 32)
    matrix = sprintf('H80x400_R080_q%i_reg%i.alist',qq, weight);
elseif (qq == 64)
    matrix = sprintf('H67x334_R080_q%i_reg%i.alist',qq, weight);
end

load(sprintf('result_q=%i_ldpc=%s_decoder=5_iter=10.mat',qq, matrix))
semilogy(snr_array, fer,'LineWidth',2)
grid on
hold on
load(sprintf('result_q=%i_ldpc=%s_decoder=6_iter=10.mat',qq, matrix))
semilogy(snr_array, fer,'LineWidth',2)
for i = 1:weight
    load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',qq, matrix, i))
    semilogy(snr_array, fer,'LineWidth',2)
end
hold off
if (weight == 3)
    legend({sprintf('Q = %i, weight = %i, FER Majority ', qq, weight), sprintf('Q = %i, weight = %i, FER Majority Seq', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 1', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 2', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 3', qq, weight)},'Location', 'southwest')
elseif (weight == 5)
    legend({sprintf('Q = %i, weight = %i, FER Majority ', qq, weight), sprintf('Q = %i, weight = %i, FER Majority Seq', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 1', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 2', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 3', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 4', qq, weight),sprintf('Q = %i, weight = %i, FER Threshold 5', qq, weight)},'Location', 'southwest')
elseif (weight == 7)
    legend({sprintf('Q = %i, weight = %i, FER Majority ', qq, weight), sprintf('Q = %i, weight = %i, FER Majority Seq', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 1', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 2', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 3', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 4', qq, weight),sprintf('Q = %i, weight = %i, FER Threshold 5', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 6 ', qq, weight), sprintf('Q = %i, weight = %i, FER Threshold 7', qq, weight)},'Location', 'southwest')
end
xlabel('SNR') 
ylabel('FER') 
title(sprintf('Comparison of FER for Q = %i, weight = %i', qq, weight))
saveas(gcf,sprintf('FER_Q=%i_weight=%i.png', qq, weight))
