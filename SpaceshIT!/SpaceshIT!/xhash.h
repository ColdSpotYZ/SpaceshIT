#pragma once
#include <string>

class XHASH
{
	protected:
		typedef unsigned char uint8;
		typedef unsigned int uint32;
		typedef unsigned long long uint64;
		
		const static uint32 xhash_const[];
		static const unsigned int xhash_BLOCK_SIZE = (512 / 8);
		
		std::string chunks[16]; // 16 chunks of 32-bit array words

	public:
		XHASH(std::string input);
		void init();
		void update(const unsigned char* message, unsigned int len);
		void final(unsigned char* digest);
		static const unsigned int DIGEST_SIZE = 32;
		int intToBinary(int n);
		std::string paddingBinary(int num, int paddedLength);
		std::string paddingBinary(std::string num, int paddedLength);

	protected:
		unsigned int m_tot_len;
		unsigned int m_len;
		uint32 m_h[8];



};

std::string xhash(std::string input);
