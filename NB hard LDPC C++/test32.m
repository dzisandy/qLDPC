%Running the  simulation for Q = 32, creating files for plotting
fe = 20;
snr = 1:0.5:8.5;
addpath encoder;
addpath decoder;
addpath ./tools/conv/;
matrix_q_16 = ['H100x500_R080_q16_reg3.alist'; 'H100x500_R080_q16_reg5.alist';'H100x500_R080_q16_reg7.alist'];
matrix_q_8 = ['H133x667_R080_q8_reg3.alist'; 'H133x667_R080_q8_reg5.alist'; 'H133x667_R080_q8_reg7.alist'];
matrix_q_32 = ['H80x400_R080_q32_reg3.alist'; 'H80x400_R080_q32_reg5.alist'; 'H80x400_R080_q32_reg7.alist'];

for qq = [32]
    if (qq == 8)
        for ii = 1:3
            for i = 5:7
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[0]);
            end
            if (ii == 1)
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[2,1,0]);
            elseif (ii == 2)
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
            elseif (ii == 3)
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_8(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
            end  
                
        end    
    elseif (qq == 16)
        for ii = 1:3
            for i = 5:7
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[0]);
            end
            if (ii == 1)
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[2,1,0]);
            elseif (ii == 2)
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
            elseif (ii == 3)
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_16(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
            end  
                
        end  
    elseif (qq == 32)
        for ii = 1:3
            for i = 5:7
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[0]);
            end
            if (ii == 1)
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[2,1,0]);
            elseif (ii == 2)
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
            elseif (ii == 3)
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[3,2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[4,3,2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[5,4,3,2,1,0]);
                simulate(matrix_q_32(ii,:),i, 10, snr, fe,[6,5,4,3,2,1,0]);
            end  
                
        end    
        
    end
end

exit();