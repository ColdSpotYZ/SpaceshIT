#include "stdafx.h"
#include "xhash.h"

XHASH::XHASH(std::string input)
{
	this->init();
	this->update((unsigned char*)input.c_str(), input.length());
	this->final();
}

// Initialize Constants (Random can change to anything)
void XHASH::init()
{
    m_h[0] = "11010100000100111100110011011110";
    m_h[1] = "10111011011001111010111010001010";
    m_h[2] = "11110001101110111100110111010001";
    m_h[3] = "10100101010011111111010100110101";
    m_h[4] = "10100010000111001010010011101111";
    m_h[5] = "10011011000001010110100010001011";
    m_h[6] = "11111100000111101100110101010111";
    m_h[7] = "10110111110000011001101000101101";
    m_len = 0;
    m_tot_len = 0;

    for (int i = 0; i < 16; i++)
    {
        chunks[i] = "";
    }
    finalHash = "";
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
    block = paddingBinary_back(block += "1", 448);
    // length
    block += paddingBinary(intToBinary(lenofeightbitASCII), 64); // the length of the block is now 512

    int count;
    for (int i = 1; i < 17; i++) // Splitting the block into 16 32-bit words
    {
        for (int ii = 1; ii < 33; ii++)
        {
            count = (i * ii) - 1;
            chunks[i-1] += block[count];
        }
    }
    for (int i = 0; i < 16; i++) // XOR the chunks 
    {
        n_chunks[i] = XOR(chunks[i], chunks[(2 * i) % 16], 32);
        n_chunks[i] = bitshift(n_chunks[i], ((i*2%3) + 1));
    }
    
}

void XHASH::final()
{
    for (int i = 0; i < 8; i++)
    {
        n_chunks[i] = XOR(m_h[i], n_chunks[i], 32);
        finalHash += GetHexFromBin(n_chunks[i]);
    }
    finalHash.insert(0, "0x");
}


std::string XHASH::XOR(string first, string second, int len)
{
    string xored = "";
    for (int i = 0; i < len; i++)
    {
        // If the Character matches 
        if (first[i] == second[i])
            xored += "0";
        else
            xored += "1";
    }
    return xored;
}

std::string XHASH::bitshift(std::string val, int num)
{
    for (int i = 0; i < num; i++)
    {
        val.erase(val.end());
        val.insert(0, "0");
    }
    return val;
}

// Recursion to convert into the Binary
int XHASH::intToBinary(int n)
{
    if (n == 0) // Base case
        return NULL;

    intToBinary(n / 2);
    return n % 2;
}

int XHASH::binarytoInt(string binary, int i)
{
    // If we reached last character 
    int n = binary.length();
    if (i == n - 1)
        return binary[i] - '0';

    // Add current tern and recur for 
    // remaining terms 
    return ((binary[i] - '0') << (n - i - 1)) +
        binarytoInt(binary, i + 1);
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

std::string XHASH::paddingBinary_back(string num, int paddedLength)
{
    while (num.size() % paddedLength != 0) // padding 0s at the back of the string
        num += '0';

    return num;

}

std::string XHASH::getHash()
{
    return this->finalHash;
}

string XHASH::GetHexFromBin(string sBinary)
{
    string rest(""), tmp, chr = "0000";
    int len = sBinary.length() / 4;
    chr = chr.substr(0, len);
    sBinary = chr + sBinary;
    for (int i = 0; i < sBinary.length(); i += 4)
    {
        tmp = sBinary.substr(i, 4);
        if (!tmp.compare("0000"))
        {
            rest = rest + "0";
        }
        else if (!tmp.compare("0001"))
        {
            rest = rest + "1";
        }
        else if (!tmp.compare("0010"))
        {
            rest = rest + "2";
        }
        else if (!tmp.compare("0011"))
        {
            rest = rest + "3";
        }
        else if (!tmp.compare("0100"))
        {
            rest = rest + "4";
        }
        else if (!tmp.compare("0101"))
        {
            rest = rest + "5";
        }
        else if (!tmp.compare("0110"))
        {
            rest = rest + "6";
        }
        else if (!tmp.compare("0111"))
        {
            rest = rest + "7";
        }
        else if (!tmp.compare("1000"))
        {
            rest = rest + "8";
        }
        else if (!tmp.compare("1001"))
        {
            rest = rest + "9";
        }
        else if (!tmp.compare("1010"))
        {
            rest = rest + "A";
        }
        else if (!tmp.compare("1011"))
        {
            rest = rest + "B";
        }
        else if (!tmp.compare("1100"))
        {
            rest = rest + "C";
        }
        else if (!tmp.compare("1101"))
        {
            rest = rest + "D";
        }
        else if (!tmp.compare("1110"))
        {
            rest = rest + "E";
        }
        else if (!tmp.compare("1111"))
        {
            rest = rest + "F";
        }
        else
        {
            continue;
        }
    }
    return rest;
}

std::string xhash(std::string input)
{
    XHASH temp = XHASH(input);
    return temp.getHash();
}