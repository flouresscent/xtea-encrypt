# XTEA Data encryption Algorithm

## Cipher Properties
The cipher is based on operations with a 64-bit block, has 32 full cycles, in each full cycle there are two rounds of the Feistel Network, which means 64 rounds of the Feistel network. However, the number of rounds to achieve better diffusion may be increased to the detriment of performance. In addition, XTEA uses a 128-bit key consisting of four 32-bit words K[0], K[1], K[2] and K[3]. XTEA does not have a key scheduling algorithm in the usual sense. In order to determine which of the four key words to use in each round, the algorithm uses the constant δ = 9E3779B9<sub>16</sub>. In TEA, there is no such distribution. Another difference from TEA is the permutation of bit operations used in the cipher. Thanks to these improvements, XTEA has not undergone strong complications compared to TEA, but at the same time eliminated two main drawbacks of the TEA algorithm:

1. each key in TEA is equivalent to the other three, which means that the effective key length is 126 bits instead of 128, as it was intended by the developers;
2. TEA is susceptible to attacks on linked keys. Such an attack may require as little as 2<sup>23</sup> selected plaintext and have a time complexity equal to 2<sup>32</sup>.

## Realization

``` cpp
#include <stdint.h>

void xtea_encipher(unsigned int num_rounds, uint32_t *v, uint32_t const *k) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], sum=0, delta=0x9E3779B9;
    
    ...
}

void xtea_decipher(unsigned int num_rounds, uint32_t *v, uint32_t const *k) {
    unsigned int i;
    uint32_t v0=v[0], v1=v[1], delta=0x9E3779B9, sum=delta*num_rounds;
    
    ...
}
```
* v — the source text consisting of two 32-bit words
* k — key consisting of four 32-bit words
* num_rounds — the number of algorithm cycles (32 is recommended)

## Some parameters of the implemented cipher

| Encryption time    	|          45.13 Mb/s          	|
|--------------------	|:----------------------------:	|
| Decryption time    	|          44.59 Mb/s          	|
| Key selection time 	| ~1.85·10<sup>24</sup> years  	|

*These parameters are designed for an Intel(R) Core(TM) i5-8300R processor with a frequency of 2.30 GHz 2.30 GHz and 16GB RAM

## Some links
1. [Wiki](https://ru.wikipedia.org/wiki/XTEA#:~:text=В%20криптографии%2C%20XTEA%20(eXtended%20TEA),к%20памяти%20и%20простоте%20реализации)
