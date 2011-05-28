#include "UTFConvert.h"


#define         MASKBITS                0x3F //00111111
#define         MASK1BYTE               0x80 //10000000
#define         MASK2BYTES              0xC0 //11000000
#define         MASK3BYTES              0xE0 //11100000
#define         MASK4BYTES              0xF0 //11110000
#define         MASK5BYTES              0xF8 //11111000
#define         MASK6BYTES              0xFC //11111100

using namespace RedBox;


std::string UTFConvert::encodeToUTF8(RB_String32 UTF32String){
	
	std::string UTF8String;
	
	for (RB_String32::iterator i=UTF32String.begin() ; i < UTF32String.end(); i++ )
	{
		// 0xxxxxxx
		if(*i < 0x80)
		{
			UTF8String.push_back((char)*i);
		}
		// 110xxxxx 10xxxxxx
		else if(*i < 0x800)
		{
			UTF8String.push_back((char)(MASK2BYTES | *i >> 6));
			UTF8String.push_back((char)(MASK1BYTE | *i & MASKBITS));
		}
		// 1110xxxx 10xxxxxx 10xxxxxx
		else if(*i < 0x10000)
		{
			UTF8String.push_back((char)(MASK3BYTES | *i >> 12));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 6 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i & MASKBITS));
		}
		// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if(*i < 0x200000)
		{
			UTF8String.push_back((char)(MASK4BYTES | *i >> 18));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 12 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 6 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i & MASKBITS));
		}
		// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if(*i < 0x4000000)
		{
			UTF8String.push_back((char)(MASK5BYTES | *i >> 24));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 18 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 12 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 6 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i & MASKBITS));
		}
		// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if(*i < 0x8000000)
		{
			UTF8String.push_back((char)(MASK6BYTES | *i >> 30));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 18 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 12 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i >> 6 & MASKBITS));
			UTF8String.push_back((char)(MASK1BYTE | *i & MASKBITS));
		}
	}
	return UTF8String;
	
}


RB_String32 UTFConvert::decodeUTF8(std::string UTF8String){
	
	
	RB_String32 UTF32String;
	
	for (std::string::iterator i=UTF8String.begin() ; i < UTF8String.end();)
	{
		RB_Char32 a32Char;
		
		// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		if((*i & MASK6BYTES) == MASK6BYTES)
		{
			a32Char = ((*i & 0x01) << 30) | ((*(i+1) & MASKBITS) << 24)
			| ((*(i+2) & MASKBITS) << 18) | ((*(i+3)
											  & MASKBITS) << 12)
			| ((*(i+4) & MASKBITS) << 6) | (*(i+5) & MASKBITS);
			i += 6;
		}
		// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if((*i & MASK5BYTES) == MASK5BYTES)
		{
			a32Char = ((*i & 0x03) << 24) | ((*(i+1)
											  & MASKBITS) << 18)
			| ((*(i+2) & MASKBITS) << 12) | ((*(i+3)
											  & MASKBITS) << 6)
			| (*(i+4) & MASKBITS);
			i += 5;
		}
		// 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
		else if((*i & MASK4BYTES) == MASK4BYTES)
		{
			a32Char = ((*i & 0x07) << 18) | ((*(i+1)
											  & MASKBITS) << 12)
			| ((*(i+2) & MASKBITS) << 6) | (*(i+3) & MASKBITS);
			i += 4;
		}
		// 1110xxxx 10xxxxxx 10xxxxxx
		else if((*i & MASK3BYTES) == MASK3BYTES)
		{
			a32Char = ((*i & 0x0F) << 12) | ((*(i+1) & MASKBITS) << 6)
			| (*(i+2) & MASKBITS);
			i += 3;
		}
		// 110xxxxx 10xxxxxx
		else if((*i & MASK2BYTES) == MASK2BYTES)
		{
			a32Char = ((*i & 0x1F) << 6) | (*(i+1) & MASKBITS);
			i += 2;
		}
		// 0xxxxxxx
		else if(*i < MASK1BYTE)
		{
			a32Char = *i;
			i += 1;
		}
		UTF32String.push_back(a32Char);
	}
	
	return UTF32String;
}