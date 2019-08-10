function [total_ace, local_aces] = calc_ace(q, factor, H_exp, H_q, max_depth)
    [m, n] = size(H_exp);
    local_aces = cell(1, n);
    total_ace = -1*ones(1, max_depth/2 - 1);
    
    H_base = H_exp~=-1;
    for col = 1:n
        disp(sprintf('col=%d', col));
        local_aces{col} = -1*ones(1, max_depth/2 - 1);
        cycles = recursCyclesGet(col, col, 0, H_base, max_depth, []);
        if isempty(cycles)
            continue;
        end

        current_ace = -1*ones(1, max_depth/2 - 1);
        for kk = 1:length(cycles)
            cycle = cycles{kk};

            odd_pos = sub2ind([m, n], cycle(2:2:end)-n, cycle(1:2:end));
            odd_off_values = H_exp(odd_pos);
            odd_nb_values = H_q(odd_pos);


            cycle = circshift(cycle', -1)';
            even_pos = sub2ind([m, n], cycle(1:2:end)-n, cycle(2:2:end));
            even_off_values = H_exp(even_pos);
            even_nb_values = H_q(even_pos);


            log_det_off = sum(odd_off_values-even_off_values);
            log_det_nb = sum(odd_nb_values-even_nb_values);

            cycle_len = length(cycle);

            for multiplicity = 1:floor(max_depth/cycle_len)
                if (mod(multiplicity*log_det_off, factor) == 0) && ...
                   (mod(multiplicity*log_det_nb, q-1) == 0)     
                    % we have a cycle => calculate ACE
                    cycle_len = multiplicity*length(cycle);
                    var_nodes = cycle(2:2:end);
                    ace = multiplicity*sum(sum(H_base(:, var_nodes), 1)) - cycle_len;
                    if (current_ace(cycle_len/2 - 1) == -1) || ...
                       (ace < current_ace(cycle_len/2 - 1))     
                        current_ace(cycle_len/2 - 1) = ace;
                    end
                    if (total_ace(cycle_len/2 - 1) == -1) || ...
                       (ace < total_ace(cycle_len/2 - 1))     
                        total_ace(cycle_len/2 - 1) = ace;
                    end
                    break;
                end
            end
        end
        
        local_aces{col} = current_ace;
    end
end

