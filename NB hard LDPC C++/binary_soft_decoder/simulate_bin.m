function simulate_bin(ldpc_filename, decoder, iter, snr_array, fe ,thetas, H)
    % initialize LDPC 
    [h, q] = alist2sparse(ldpc_filename);
    q = 2;
    %init_ldpc = @(x) decode_soft(0, x);
    if (q == 2)
        init_ldpc = @(x) decode_soft(0, x);
        decode_ldpc = @(decoder, ldpc, iter, x, thetas, thetas_num) decode_soft(decoder, ldpc, iter, x, thetas, thetas_num);
    end
    %decode_ldpc = @(decoder, ldpc, iter, x, thetas, thetas_num) decode_soft(decoder, ldpc, iter, x, thetas, thetas_num);
    
    [H, G] = ldpc_h2g(h,q);
    [K, N] = size(G);
    R = K/N;
    bN = N*log2(q);
    temp = strcat(ldpc_filename, '.temp');
    sparse2alist(q, H, temp);
    [ldpc, ~, ~] = init_ldpc(temp);

    M = 2;
    hMod = modem.pskmod('M', 2);
    Es = mean(modulate(hMod, [0:M-1]).*conj(modulate(hMod, [0:M-1])));

    in_ber = zeros(1, length(snr_array));
    ber = zeros(1, length(snr_array));
    in_ser = zeros(1, length(snr_array));
    ser = zeros(1, length(snr_array));
    fer = zeros(1, length(snr_array));

    for ii = 1:length(snr_array)
        % NEW SNR
        snr = snr_array(ii);
        sigma = sqrt(Es*(10^(-snr/10))/2); %N0 = 2*sigma^2
        
        disp(sprintf('\n\n========== SNR = %f, EbN0 = %f, sigma = %1.2e ===========', snr, snr-10*log10(R*log2(M)), sigma/sqrt(Es)));
        
        tests = 0;
        wrong_dec = 0;
        in_errors = 0;
        in_bit_errors = 0;
        errors = 0;
        bit_errors = 0;
        
        while wrong_dec  < fe
            tests = tests + 1;
            
            % generate inf. word 
            iwd = randi(q, 1, K) - 1;

            % encode by outer code
            cwd = ldpc_encode(iwd, G, q);
            bcwd = de2bi(cwd, log2(q)); 
            bcwd = reshape(transpose(bcwd), 1, N*log2(q));

            % add noise
            tx = real(modulate(hMod, bcwd));
            noise_vector = randn(1,bN)*sigma;
            rx = tx + noise_vector;

            % demodulate
            in_llrs = demodulate_bpsk(q, hMod, rx, sigma);

            [temp, index] = max(in_llrs);
            rx_cwd = index - 1;

            in_error_indexes = find(cwd ~= rx_cwd);
            in_errors = in_errors + length(in_error_indexes);
            in_bit_errors = in_bit_errors + bit_weight(bitxor(cwd, rx_cwd));

            % decode
            %disp('cdw = ');
            %disp(cwd);
            
            [result, iter, est_cwd] = decode_ldpc(decoder, ldpc, rx_cwd, iter, thetas, length(thetas));
            %disp('est = ')
            %disp(est_cwd);
            error_indexes = find(cwd ~= est_cwd);
            if ~isempty(error_indexes)
                wrong_dec = wrong_dec + 1;
                errors = errors + length(error_indexes);
                bit_errors = bit_errors + bit_weight(bitxor(cwd, est_cwd));
                in_ser(ii) = in_errors/N/tests;
                in_ber(ii) = in_bit_errors/N/log2(q)/tests;
                fer(ii) = wrong_dec/tests;
                ser(ii) = errors/N/tests;
                ber(ii) = bit_errors/N/log2(q)/tests;

                disp(sprintf('\tin_ser = %f, in_ber = %f, fer = %f, ser = %f ber = %f' , in_ser(ii), in_ber(ii), fer(ii), ser(ii), ber(ii)));
                %save(sprintf('result_q=%d_ldpc=%s_decoder=%d_iter=%d.mat', q, ldpc_filename, decoder, iter));
                if (decoder == 9)
                    save(sprintf('result_q=%d_ldpc=%s_decoder=%d_iter=%d_thetas_num=%d.mat', q, ldpc_filename, decoder, iter, length(thetas)));
                else
                    save(sprintf('result_q=%d_ldpc=%s_decoder=%d_iter=%d.mat', q, ldpc_filename, decoder, iter));
                end
            
            end
        end
        if (decoder == 9)
            save(sprintf('result_q=%d_ldpc=%s_decoder=%d_iter=%d_thetas_num=%d.mat', q, ldpc_filename, decoder, iter, length(thetas)));
        else
            save(sprintf('result_q=%d_ldpc=%s_decoder=%d_iter=%d.mat', q, ldpc_filename, decoder, iter));
        end
        
        if fer(ii) < 1e-3
            break;
        end
   end
    
end

function result = bit_weight(v)
    result = sum(sum(de2bi(v)));
end