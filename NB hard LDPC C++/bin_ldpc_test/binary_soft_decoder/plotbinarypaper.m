for i = [3,5,7,9]
    if (i == 3 )
        matrix = sprintf('H400x2000_R080_q2_reg%i.alist', i);
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat', matrix))
        semilogy(snr_array, fer,'-r','Linestyle','--', 'LineWidth', 2)
        grid on;
        hold on;
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=%i.mat',matrix,i))
        semilogy(snr_array, fer,'-r','Linestyle','-', 'LineWidth', 2)
    elseif (i == 5)
        matrix = sprintf('H400x2000_R080_q2_reg%i.alist', i);
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat',matrix))
        semilogy(snr_array, fer,'-b','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=%i.mat',matrix,i))
        semilogy(snr_array, fer,'-b', 'LineWidth', 2)
    elseif (i == 7)
        matrix = sprintf('H400x2000_R080_q2_reg%i.alist',i);
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat', matrix))
        semilogy(snr_array, fer,'-g','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=%i.mat', matrix,i))
        semilogy(snr_array, fer,'-g','Linestyle','-', 'LineWidth', 2)
    elseif (i == 9)
        matrix = sprintf('H400x2000_R080_q2_reg%i.alist', i);
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat', matrix))
        semilogy(snr_array, fer,'-k','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=2_ldpc=%s_decoder=9_iter=10_thetas_num=%i.mat', matrix,i))
        semilogy(snr_array, fer,'-k','Linestyle','-', 'LineWidth', 2)
    end
end
title('Comparison of single/multiple treshold decoder for different weights')
legend({'weight = 3, single','weight = 3, multiple','weight = 5, single','weight = 5, multiple','weight = 7, single','weight = 7, multiple','weight = 9, single','weight = 9, multiple'},'Location', 'southwest')
saveas(gcf,'binary_comparison.png')