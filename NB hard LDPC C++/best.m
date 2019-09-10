weight = 9;
qq = 8;
i = 9;
matrix = sprintf('H133x667_R080_q%i_reg%i.alist',qq, weight);
load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',qq, matrix, i))
semilogy(snr_array, fer,'LineWidth',2)
grid on
hold on
for qq = [4,16,32,64]
    if (qq == 16)
        matrix = sprintf('H100x500_R080_q%i_reg%i.alist',qq, weight);
    elseif (qq == 32)
        matrix = sprintf('H80x400_R080_q%i_reg%i.alist',qq, weight);
    elseif (qq == 64)
        matrix = sprintf('H67x334_R080_q%i_reg%i.alist',qq, weight);
    elseif (qq == 4)
        matrix = sprintf('H200x1000_R080_q%i_reg%i.alist',qq, weight);
    end
 load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',qq, matrix, i))
 semilogy(snr_array, fer,'LineWidth',2)
end
xlabel('SNR') 
ylabel('FER') 
title(sprintf('Best performance on weight = %i', weight));
legend({sprintf('Q = 8, weight = %i',weight), sprintf('Q = 4, weight = %i',weight), sprintf('Q = 16, weight = %i', weight), sprintf('Q = 32, weight = %i', weight), sprintf('Q = 64, weight = %i',weight) },'Location', 'southwest')
saveas(gcf,sprintf('Best_weight=%i.png', weight))
