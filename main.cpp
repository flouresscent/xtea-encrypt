#include <iostream>
#include <cstring>

using namespace std;

#define BLOCK_SIZE 8

const uint32_t key[4] = {0xFDA5, 0xD54E, 0xFC00, 0xB55A};

void xtea_encipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;
    
    for (i = 0; i < num_rounds; i++) {
        v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        sum += delta;
        v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    }
    
    v[0] = v0; v[1] = v1;
}

void xtea_decipher(unsigned int num_rounds, uint32_t v[2], uint32_t const key[4]) {
    unsigned int i;
    uint32_t v0 = v[0], v1=v[1], delta = 0x9E3779B9, sum = delta * num_rounds;
    
    for (i = 0; i < num_rounds; i++) {
        v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        sum -= delta;
        v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    }
    
    v[0] = v0; v[1] = v1;
}


void encrypt_decrypt(char *inout, int len, bool encrypt) {
    for(int i = 0; i < len / BLOCK_SIZE; i++) {
        if (encrypt)
            xtea_encipher(32,(uint32_t*)(inout+(i*BLOCK_SIZE)),key);
        else
            xtea_decipher(32,(uint32_t*)(inout+(i*BLOCK_SIZE)),key);
    }
  
    if (len % BLOCK_SIZE != 0) {
        int mod = len % BLOCK_SIZE;
        int offset = (len / BLOCK_SIZE) * BLOCK_SIZE;
        char data[BLOCK_SIZE];
        memcpy(data, inout + offset, mod);

        if (encrypt)
            xtea_encipher(32, (uint32_t*)data, key);
        else
            xtea_decipher(32, (uint32_t*)data, key);

        memcpy(inout + offset, data, mod);
    }
}

int main() {
    char str[32] = {"Hello, word!"};
    int len = sizeof(str);

    encrypt_decrypt(str, len, true);
    cout << str;
    
    encrypt_decrypt(str, len, false);
    cout << str;

    return 0;
}
