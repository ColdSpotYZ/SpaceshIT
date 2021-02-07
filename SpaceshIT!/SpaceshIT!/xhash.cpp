#include "stdafx.h"
#include "xhash.h"

XHASH::XHASH(std::string input)
{
    unsigned char digest[XHASH::DIGEST_SIZE];
    memset(digest, 0, XHASH::DIGEST_SIZE);

	this->init();
	this->update((unsigned char*)input.c_str(), input.length());
	this->final(digest);
}

// Initialize Constants (Random can change to anything)
void XHASH::init()
{
    m_h[0] = 0x6a09e667;
    m_h[1] = 0xbb67ae85;
    m_h[2] = 0x3c6ef372;
    m_h[3] = 0xa54ff53a;
    m_h[4] = 0x510e527f;
    m_h[5] = 0x9b05688c;
    m_h[6] = 0x1f83d9ab;
    m_h[7] = 0x5be0cd19;
    m_len = 0;
    m_tot_len = 0;

    for (int i = 0; i < 16; i++)
    {
        chunks[i] = "";
    }
}

void XHASH::update(const unsigned char* message, unsigned int len)
{
    // Message 
    std::string block = "";
    int lenofeightbitASCII = 0;
    int BinaryMessage;
    for (int i = 0; i < len; i++)
    {
        BinaryMessage = intToBinary(message[i]);
        lenofeightbitASCII += to_string(BinaryMessage).length();
        block += paddingBinary(BinaryMessage, 8);
    }
    // Ensure that the output is always fixed
    block = paddingBinary(block += "1", 512); 
    block = paddingBinary(std::stoll(block) % 448, 448);

    // length
    block += paddingBinary(lenofeightbitASCII, 64); // the length of the block is now 512
    int count;
    for (int i = 1; i < 17; i++) // Splitting the block into 16 32-bit words
    {
        for (int ii = 1; ii < 33; ii++)
        {
            count = (i * ii) - 1;
            chunks[i-1] += block[count];
        }
    }

}

void XHASH::final(unsigned char* digest)
{

}


std::string xhash(std::string input)
{
	XHASH temp = XHASH(input);
    return "";
}

// Recursion to convert into the Binary
int XHASH::intToBinary(int n)
{
    if (n == 0) // Base case
        return NULL;

    intToBinary(n / 2);
    return n % 2;
}

std::string XHASH::paddingBinary(int num, int paddedLength)
{
    string paddedBinary = to_string(num);

    std::reverse(paddedBinary.begin(), paddedBinary.end()); // Reversing the string to pad 0s
    while (paddedBinary.size() % paddedLength != 0) // padding 0s at the back of the string
        paddedBinary += '0';

    std::reverse(paddedBinary.begin(), paddedBinary.end()); // Reversing the string back

    return paddedBinary;

}

std::string XHASH::paddingBinary(string num, int paddedLength)
{
    std::reverse(num.begin(), num.end()); // Reversing the string to pad 0s
    while (num.size() % paddedLength != 0) // padding 0s at the back of the string
        num += '0';

    std::reverse(num.begin(), num.end()); // Reversing the string back

    return num;

}
