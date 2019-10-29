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
1. Effect of multi-threshold decoding on binary performance:
  ![alt tag](https://github.com/dzisandy/qLDPC/blob/master/NB%20hard%20LDPC%20C%2B%2B/Inputber.png)  
2. Comparison of performance in terms of BER:

3. Comparison of performance in terms of SER:

4. Optimization in case of performance for different matrices

## Research Group
* Andrei Dzis
* Alexey Frolov
* Pavel Rybin

## Copyright
© 2019, Moscow.


