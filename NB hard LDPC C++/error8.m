fe = 20;
snr = 1:0.5:8.5;
addpath encoder;
addpath decoder;
addpath ./tools/conv/;
i = 7;
matrix_q_64 = ['H67x334_R080_q64_reg3.alist'; 'H67x334_R080_q64_reg5.alist';'H67x334_R080_q64_reg7.alist'];
matrix_q_4 = ['H200x1000_R080_q4_reg3.alist'; 'H200x1000_R080_q4_reg5.alist';'H200x1000_R080_q4_reg7.alist'];
matrix_q_16 = ['H100x500_R080_q16_reg3.alist'; 'H100x500_R080_q16_reg5.alist';'H100x500_R080_q16_reg7.alist'];
matrix_q_8 = ['H133x667_R080_q8_reg3.alist'; 'H133x667_R080_q8_reg5.alist'; 'H133x667_R080_q8_reg7.alist'];
matrix_q_32 = ['H80x400_R080_q32_reg3.alist'; 'H80x400_R080_q32_reg5.alist'; 'H80x400_R080_q32_reg7.alist'];

for qq = [8]
    if (qq == 4)
        for ii = 3
                simulate(matrix_q_4(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_4(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
        end 
    elseif (qq == 8)
        for ii = 3
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
        end 
    elseif (qq == 16)
        for ii = 3
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
        end 
    elseif (qq == 32)
        for ii = 3
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
        end 
    elseif (qq == 64)
        for ii = 3
                simulate(matrix_q_64(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_64(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
        end 
    end
                
   
end
exit();