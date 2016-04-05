#include <stdint.h>
#include <iostream>
#include "ArrayLike.hpp"

using namespace std;

// Set up array as buffer
// provide read and write functions
// to access the buffer
uint8_t mem[64*1024];

uint8_t spi_read(size_t index)
{
    return mem[index];
}

void spi_write(size_t index, uint8_t data)
{
    mem[index] = data;
}


int main()
{
    // initialize an ArrayLike using the spi_read and spi_write functions
    // specialize to uint8_t to match the signature of read and write
    ArrayLike<uint8_t> m(spi_read, spi_write);

    // set up a bare array to match the behavior
    uint8_t m2[64*1024];

    // assignment
    m[0] = 0xFF;
    m2[0] = 0xFF;
    cout << (int)m[0] << endl;
    cout << (int)m2[0] << endl;

    // reference
    uint8_t a = m[0];
    uint8_t b = m2[0];
    cout << (int)a << endl;
    cout << (int)b << endl;

    // pointer-like
    *m = 1;
    *m2 = 1;
    cout << (int)m[0] << endl;
    cout << (int)m2[0] << endl;

    // pointer-like with offset
    *(m + 2) = 3;
    *(m2 + 2) = 3;
    cout << (int)m[2] << endl;
    cout << (int)m2[2] << endl;

    // pointer-like with negative offset
    ArrayLike<uint8_t> m3 = m + 256;
    *(m3 - 250) = 6;
    cout << (int)m3[-250] << endl;
    cout << (int)m[6] << endl;

    uint8_t* m4 = m2 + 256;
    *(m4 - 250) = 6;
    cout << (int)m4[-250] << endl;
    cout << (int)m2[6] << endl;


    // pointer-like with offset and indexing
    (m + 2)[2] = 4;
    (m2 + 2)[2] = 4;
    cout << (int)m[4] << endl;
    cout << (int)m2[4] << endl;

    // loop over first 10 items
    for (int i = 0; i < 10 ; i++)
        cout << (int)m[i];
    cout << endl;

    for (int i = 0; i < 10 ; i++)
        cout << (int)m2[i];
    cout << endl;
}
