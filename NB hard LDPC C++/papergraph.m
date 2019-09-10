weight = 3;
q = 2;
matrix = sprintf('H400x2000_R080_q%i_reg%i.alist',q, weight);
load(sprintf('result_q=%i_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat',q, matrix))
semilogy(snr_array, fer,'-g','Linestyle','--', 'LineWidth', 2)
grid on;
hold on;
load(sprintf('result_q=%i_ldpc=%s_decoder=9_iter=10_thetas_num=%i.mat',q, matrix, weight))
semilogy(snr_array, fer,'-g','Linestyle','-', 'LineWidth', 2)
for q = [4,8,16,32,64]        
    if (q == 4)
        matrix = sprintf('H200x1000_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(snr_array, fer,'-r','Linestyle','--', 'LineWidth', 2)
        
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',q, matrix, weight))
        semilogy(snr_array, fer,'-r','Linestyle','-', 'LineWidth', 2)


        
    elseif (q == 8)
        matrix = sprintf('H133x667_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(snr_array, fer,'-b','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',q, matrix, weight))
        semilogy(snr_array, fer,'-b','Linestyle','-', 'LineWidth', 2)


    elseif (q == 16)
        matrix = sprintf('H100x500_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(snr_array, fer,'-c','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',q, matrix, weight))
        semilogy(snr_array, fer,'-c','Linestyle','-', 'LineWidth', 2)
    elseif (q == 32)
        matrix = sprintf('H80x400_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(snr_array, fer,'-m','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',q, matrix, weight))
        semilogy(snr_array, fer,'-m','Linestyle','-', 'LineWidth', 2)
    elseif (q == 64)
        matrix = sprintf('H67x334_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(snr_array, fer,'-k','Linestyle','--', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=%i.mat',q, matrix, weight))
        semilogy(snr_array, fer,'-k','Linestyle','-', 'LineWidth', 2)

    end
end

title(sprintf('Comparison single/multiple threshold performance on weight = %i', weight));
xlabel('SNR') 
ylabel('FER') 
legend({'Q = 2, single','Q = 2, multiple','Q = 4, single','Q = 4, multiple','Q = 8, single','Q = 8, multiple','Q = 16, single','Q = 16, multiple','Q = 32, single','Q = 32, multiple','Q = 64, single','Q = 64, multiple'
},'Location', 'southwest')
saveas(gcf,sprintf('Compare_weight=%i.png', weight))
