#pragma once
#include <string>

class XHASH
{
	private:
		std::string finalHash;
	protected:
		typedef unsigned char uint8;
		typedef unsigned int uint32;
		typedef unsigned long long uint64;
		
		const static uint32 xhash_const[];
		static const unsigned int xhash_BLOCK_SIZE = (512 / 8);
		
		std::string chunks[16]; // 16 chunks of 32-bit array words
		std::string n_chunks[16]; // 16 chunks of XORED 32-bit array words

	public:
		XHASH(std::string input);
		void init();
		void update(const unsigned char* message, unsigned int len);
		void final();
		std::string XOR(string first, string second, int len);
		int intToBinary(int n);
		int binarytoInt(string binary, int i);
		std::string bitshift(std::string val, int num);
		std::string paddingBinary(int num, int paddedLength);
		std::string paddingBinary_back(std::string num, int paddedLength);
		string GetHexFromBin(string sBinary);
		std::string getHash();

	protected:
		unsigned int m_tot_len;
		unsigned int m_len;
		std::string m_h[8];



};

std::string xhash(std::string input);
