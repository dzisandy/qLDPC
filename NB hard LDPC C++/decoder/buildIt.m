function buildIt(q_array)

if isempty(q_array)
    q_array = [2 4 8 16 32 64 256];
end

for i = 1:length(q_array)
    q = q_array(i);
    switch q
        case 2
            mex -O decode_soft.cpp -DLOG_Q=1 -I../common -output decode_soft_2
        case 4
            mex -O decode_soft.cpp -DLOG_Q=2 -I../common -output decode_soft_4
        case 8
            mex -O decode_soft.cpp -DLOG_Q=3 -I../common -output decode_soft_8
        case 16
            mex -O decode_soft.cpp -DLOG_Q=4 -I../common -output decode_soft_16
        case 32
            mex -O decode_soft.cpp -DLOG_Q=5 -I../common -output decode_soft_32
        case 64
            mex -O decode_soft.cpp -DLOG_Q=6 -I../common -output decode_soft_64
        case 256
            mex -O decode_soft.cpp -DLOG_Q=8 -I../common -output decode_soft_256
        otherwise
            error('Not supported!')
    end
end

end

