for q = [2,4,8,16,32,64]  
    if (q == 2)
        weight = 5;
        matrix = sprintf('H400x2000_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=9_iter=10_thetas_num=5.mat',q, matrix))
        semilogy(in_ser, fer,'-g','Linestyle','-', 'LineWidth', 2)
        grid on;
        hold on;
        load(sprintf('result_q=%i_ldpc=%s_decoder=9_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-g','Linestyle','--', 'LineWidth', 2)
    elseif (q == 4)
        weight = 9;
        matrix = sprintf('H200x1000_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=9.mat',q, matrix))
        semilogy(in_ser, fer,'-r','Linestyle','-', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-r','Linestyle','--', 'LineWidth', 2)
    elseif (q == 8)
        weight = 7;
        matrix = sprintf('H133x667_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=7.mat',q, matrix))
        semilogy(in_ser, fer,'-b','Linestyle','-', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-b','Linestyle','--', 'LineWidth', 2)
    elseif (q == 16)
        weight = 7;
        matrix = sprintf('H100x500_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-c','Linestyle','-', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-c','Linestyle','--', 'LineWidth', 2)
    elseif (q == 32)
        weight = 7;
        matrix = sprintf('H80x400_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=7.mat',q, matrix))
        semilogy(in_ser, fer,'-k','Linestyle','-', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-k','Linestyle','--', 'LineWidth', 2)
    elseif (q == 64)
        weight = 7;
        matrix = sprintf('H67x334_R080_q%i_reg%i.alist',q, weight);
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=7.mat',q, matrix))
        semilogy(in_ser, fer,'-m','Linestyle','-', 'LineWidth', 2)
        load(sprintf('result_q=%i_ldpc=%s_decoder=7_iter=10_thetas_num=1.mat',q, matrix))
        semilogy(in_ser, fer,'-m','Linestyle','--', 'LineWidth', 2)
    end
end

title('Comparison of the performance for different Q');
xlabel('Input SER') 
xlim([0 0.05])
ylabel('FER') 
legend({'Q = 2, multi-threshold','Q = 2, single-threshold', 'Q = 4, multi-threshold','Q = 4, single-threshold', 'Q = 8, multi-threshold','Q = 8, single-threshold', 'Q = 16, multi-threshold','Q = 16, single-threshold', 'Q = 32, multi-threshold','Q = 32, single-threshold', 'Q = 64, multi-threshold','Q = 64, single-threshold' 
},'Location', 'southeast')
saveas(gcf,'Inputser.png')
