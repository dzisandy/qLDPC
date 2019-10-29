# ON THE MULTIPLE THRESHOLD DECODING OF LDPC CODES OVER GF(q) (qLDPC)


## About
My implementations of single/multiple threshold majority decoding algorithms. Used for paper "On the Hard-Decision Multi-Threshold Decoding of Binary and Non-Binary LDPC Codes"
The original paper by A.Frolov and V.Zyablov in "Advances in Mathematics of Communications", 2017.

[Link on paper](https://github.com/dzisandy/qLDPC/blob/master/2017_amc.pdf)


## Milestones

1. [NB hard LDPC MatLab](https://github.com/dzisandy/qLDPC/tree/master/NB%20hard%20LDPC%20MatLab)
Implemented both algorithms from paper, built up a FER/p dependency. (As ISP research project)

2. [NB hard LDPC C++](https://github.com/dzisandy/qLDPC/tree/master/NB%20hard%20LDPC%20C%2B%2B)
Implemented single/multiple threshold majority decoding algorithms from paper, based on C++, MatLab, MeX for AWGN channel , BPSK modulation. Compared with simple majority (without threshold).

3. After simple simulation results and it's obsevrance, produced paper:
  "On the Hard-Decision Multi-Threshold Decoding of Binary and Non-Binary LDPC Codes"
  
## Results
1. Effect of multi-threshold decoding on binary performance in comparison with single-threshold for different column weights of matrices:
  ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/binary_soft_decoder/binary_comparison.png)
2. Comparison of performance in terms of input Bit Error Rate (BER):
  ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Inputber.png)  
3. Comparison of performance in terms of input Symbol Error Rate (SER):
  ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Inputser.png)  
4. Optimization in case of performance for different matrices, with the given column weights: 
  * weight = 3:
    ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Compare_weight%3D3.png)  
  * weight = 5:
    ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Compare_weight%3D5.png)  
  * weight = 7:
    ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Compare_weight%3D7.png)  
  * weight = 9:
    ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Compare_weight%3D9.png)  



## Research Group
* Andrei Dzis
* Alexey Frolov
* Pavel Rybin

## Copyright
© 2019, Moscow.


