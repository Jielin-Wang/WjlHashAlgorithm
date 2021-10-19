#include "WJLHA3.h"
extern const unsigned char RandomOfUCharTable[256];
extern const unsigned char RandomOfbitTable[256];
extern const unsigned char bitOfByteTable[256][8];
extern const unsigned int Ps = 256;// Customizable
// Jielincode Encoding Struct
typedef struct
{
	unsigned int RC_CODE_BITS;
	unsigned int RC_SHIFT_BITS;
	unsigned int RC_MAX_RANGE;
	unsigned int RC_MIN_RANGE;
	double p0;
	double p1;
	double JIELINCOE;
	unsigned int EFLow;
	unsigned int EFRange;
	unsigned int EFDigits;
	unsigned int EFFollow;
	unsigned int EOut_buff_loop;
	unsigned char *HashValueBuFF;
	int HashValueBuFF_Length;
}WJLCoder;
// Random - generated byte 2D table,Customizable tables
const unsigned char RandomOfUCharTable[256] =	{
	0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
	0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
	0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
	0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
	0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
	0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
	0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
	0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
	0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
	0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
	0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
	0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
	0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
	0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
	0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
	0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};
// Random - generated bit 2D table, Customizable tables
const unsigned char RandomOfbitTable[256] =	{
	1,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,
	1,1,0,0,0,1,0,1,0,0,1,1,1,1,1,1,
	0,1,1,1,0,1,1,0,1,0,0,1,0,1,0,0,
	1,0,0,1,0,0,1,0,1,1,1,0,1,1,0,1,
	1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,
	0,0,0,1,0,1,0,0,1,1,0,0,0,0,1,0,
	1,0,1,1,1,1,0,1,0,0,0,1,1,0,0,1,
	1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,
	0,0,0,0,1,1,1,1,1,0,1,0,1,1,1,0,
	0,1,1,1,1,1,0,0,1,0,1,0,1,1,0,0,
	0,0,0,0,1,1,0,1,0,0,1,0,0,0,1,1,
	0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,
	0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,
	1,1,1,0,0,0,0,0,1,0,1,1,0,0,0,1,
	0,0,1,1,1,0,1,1,0,1,1,1,0,1,0,1,
	0,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1
};
// Bit value at each position in each byte
const unsigned char bitOfByteTable[256][8] =	{
	{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,1,0},{0,0,0,0,0,0,1,1},{0,0,0,0,0,1,0,0},{0,0,0,0,0,1,0,1},{0,0,0,0,0,1,1,0},{0,0,0,0,0,1,1,1},	//0~7
	{0,0,0,0,1,0,0,0},{0,0,0,0,1,0,0,1},{0,0,0,0,1,0,1,0},{0,0,0,0,1,0,1,1},{0,0,0,0,1,1,0,0},{0,0,0,0,1,1,0,1},{0,0,0,0,1,1,1,0},{0,0,0,0,1,1,1,1},	//8~15	
	{0,0,0,1,0,0,0,0},{0,0,0,1,0,0,0,1},{0,0,0,1,0,0,1,0},{0,0,0,1,0,0,1,1},{0,0,0,1,0,1,0,0},{0,0,0,1,0,1,0,1},{0,0,0,1,0,1,1,0},{0,0,0,1,0,1,1,1},	//16~23
	{0,0,0,1,1,0,0,0},{0,0,0,1,1,0,0,1},{0,0,0,1,1,0,1,0},{0,0,0,1,1,0,1,1},{0,0,0,1,1,1,0,0},{0,0,0,1,1,1,0,1},{0,0,0,1,1,1,1,0},{0,0,0,1,1,1,1,1},	//24~31
	{0,0,1,0,0,0,0,0},{0,0,1,0,0,0,0,1},{0,0,1,0,0,0,1,0},{0,0,1,0,0,0,1,1},{0,0,1,0,0,1,0,0},{0,0,1,0,0,1,0,1},{0,0,1,0,0,1,1,0},{0,0,1,0,0,1,1,1},	//32~39
	{0,0,1,0,1,0,0,0},{0,0,1,0,1,0,0,1},{0,0,1,0,1,0,1,0},{0,0,1,0,1,0,1,1},{0,0,1,0,1,1,0,0},{0,0,1,0,1,1,0,1},{0,0,1,0,1,1,1,0},{0,0,1,0,1,1,1,1},	//40~47
	{0,0,1,1,0,0,0,0},{0,0,1,1,0,0,0,1},{0,0,1,1,0,0,1,0},{0,0,1,1,0,0,1,1},{0,0,1,1,0,1,0,0},{0,0,1,1,0,1,0,1},{0,0,1,1,0,1,1,0},{0,0,1,1,0,1,1,1},	//48~55
	{0,0,1,1,1,0,0,0},{0,0,1,1,1,0,0,1},{0,0,1,1,1,0,1,0},{0,0,1,1,1,0,1,1},{0,0,1,1,1,1,0,0},{0,0,1,1,1,1,0,1},{0,0,1,1,1,1,1,0},{0,0,1,1,1,1,1,1},	//56~63
	{0,1,0,0,0,0,0,0},{0,1,0,0,0,0,0,1},{0,1,0,0,0,0,1,0},{0,1,0,0,0,0,1,1},{0,1,0,0,0,1,0,0},{0,1,0,0,0,1,0,1},{0,1,0,0,0,1,1,0},{0,1,0,0,0,1,1,1},	//64~71
	{0,1,0,0,1,0,0,0},{0,1,0,0,1,0,0,1},{0,1,0,0,1,0,1,0},{0,1,0,0,1,0,1,1},{0,1,0,0,1,1,0,0},{0,1,0,0,1,1,0,1},{0,1,0,0,1,1,1,0},{0,1,0,0,1,1,1,1},	//72~79
	{0,1,0,1,0,0,0,0},{0,1,0,1,0,0,0,1},{0,1,0,1,0,0,1,0},{0,1,0,1,0,0,1,1},{0,1,0,1,0,1,0,0},{0,1,0,1,0,1,0,1},{0,1,0,1,0,1,1,0},{0,1,0,1,0,1,1,1},	//80~87
	{0,1,0,1,1,0,0,0},{0,1,0,1,1,0,0,1},{0,1,0,1,1,0,1,0},{0,1,0,1,1,0,1,1},{0,1,0,1,1,1,0,0},{0,1,0,1,1,1,0,1},{0,1,0,1,1,1,1,0},{0,1,0,1,1,1,1,1},	//88~95
	{0,1,1,0,0,0,0,0},{0,1,1,0,0,0,0,1},{0,1,1,0,0,0,1,0},{0,1,1,0,0,0,1,1},{0,1,1,0,0,1,0,0},{0,1,1,0,0,1,0,1},{0,1,1,0,0,1,1,0},{0,1,1,0,0,1,1,1},	//96~103
	{0,1,1,0,1,0,0,0},{0,1,1,0,1,0,0,1},{0,1,1,0,1,0,1,0},{0,1,1,0,1,0,1,1},{0,1,1,0,1,1,0,0},{0,1,1,0,1,1,0,1},{0,1,1,0,1,1,1,0},{0,1,1,0,1,1,1,1},	//104~111
	{0,1,1,1,0,0,0,0},{0,1,1,1,0,0,0,1},{0,1,1,1,0,0,1,0},{0,1,1,1,0,0,1,1},{0,1,1,1,0,1,0,0},{0,1,1,1,0,1,0,1},{0,1,1,1,0,1,1,0},{0,1,1,1,0,1,1,1},	//112~119
	{0,1,1,1,1,0,0,0},{0,1,1,1,1,0,0,1},{0,1,1,1,1,0,1,0},{0,1,1,1,1,0,1,1},{0,1,1,1,1,1,0,0},{0,1,1,1,1,1,0,1},{0,1,1,1,1,1,1,0},{0,1,1,1,1,1,1,1},	//120~127
	{1,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,1},{1,0,0,0,0,0,1,0},{1,0,0,0,0,0,1,1},{1,0,0,0,0,1,0,0},{1,0,0,0,0,1,0,1},{1,0,0,0,0,1,1,0},{1,0,0,0,0,1,1,1},	//128~135
	{1,0,0,0,1,0,0,0},{1,0,0,0,1,0,0,1},{1,0,0,0,1,0,1,0},{1,0,0,0,1,0,1,1},{1,0,0,0,1,1,0,0},{1,0,0,0,1,1,0,1},{1,0,0,0,1,1,1,0},{1,0,0,0,1,1,1,1},	//136~143
	{1,0,0,1,0,0,0,0},{1,0,0,1,0,0,0,1},{1,0,0,1,0,0,1,0},{1,0,0,1,0,0,1,1},{1,0,0,1,0,1,0,0},{1,0,0,1,0,1,0,1},{1,0,0,1,0,1,1,0},{1,0,0,1,0,1,1,1},	//144~151
	{1,0,0,1,1,0,0,0},{1,0,0,1,1,0,0,1},{1,0,0,1,1,0,1,0},{1,0,0,1,1,0,1,1},{1,0,0,1,1,1,0,0},{1,0,0,1,1,1,0,1},{1,0,0,1,1,1,1,0},{1,0,0,1,1,1,1,1},	//152~159
	{1,0,1,0,0,0,0,0},{1,0,1,0,0,0,0,1},{1,0,1,0,0,0,1,0},{1,0,1,0,0,0,1,1},{1,0,1,0,0,1,0,0},{1,0,1,0,0,1,0,1},{1,0,1,0,0,1,1,0},{1,0,1,0,0,1,1,1},	//160~167
	{1,0,1,0,1,0,0,0},{1,0,1,0,1,0,0,1},{1,0,1,0,1,0,1,0},{1,0,1,0,1,0,1,1},{1,0,1,0,1,1,0,0},{1,0,1,0,1,1,0,1},{1,0,1,0,1,1,1,0},{1,0,1,0,1,1,1,1},	//168~175
	{1,0,1,1,0,0,0,0},{1,0,1,1,0,0,0,1},{1,0,1,1,0,0,1,0},{1,0,1,1,0,0,1,1},{1,0,1,1,0,1,0,0},{1,0,1,1,0,1,0,1},{1,0,1,1,0,1,1,0},{1,0,1,1,0,1,1,1},	//176~183
	{1,0,1,1,1,0,0,0},{1,0,1,1,1,0,0,1},{1,0,1,1,1,0,1,0},{1,0,1,1,1,0,1,1},{1,0,1,1,1,1,0,0},{1,0,1,1,1,1,0,1},{1,0,1,1,1,1,1,0},{1,0,1,1,1,1,1,1},	//184~191
	{1,1,0,0,0,0,0,0},{1,1,0,0,0,0,0,1},{1,1,0,0,0,0,1,0},{1,1,0,0,0,0,1,1},{1,1,0,0,0,1,0,0},{1,1,0,0,0,1,0,1},{1,1,0,0,0,1,1,0},{1,1,0,0,0,1,1,1},	//192~199
	{1,1,0,0,1,0,0,0},{1,1,0,0,1,0,0,1},{1,1,0,0,1,0,1,0},{1,1,0,0,1,0,1,1},{1,1,0,0,1,1,0,0},{1,1,0,0,1,1,0,1},{1,1,0,0,1,1,1,0},{1,1,0,0,1,1,1,1},	//200~207
	{1,1,0,1,0,0,0,0},{1,1,0,1,0,0,0,1},{1,1,0,1,0,0,1,0},{1,1,0,1,0,0,1,1},{1,1,0,1,0,1,0,0},{1,1,0,1,0,1,0,1},{1,1,0,1,0,1,1,0},{1,1,0,1,0,1,1,1},	//208~215
	{1,1,0,1,1,0,0,0},{1,1,0,1,1,0,0,1},{1,1,0,1,1,0,1,0},{1,1,0,1,1,0,1,1},{1,1,0,1,1,1,0,0},{1,1,0,1,1,1,0,1},{1,1,0,1,1,1,1,0},{1,1,0,1,1,1,1,1},	//216~223
	{1,1,1,0,0,0,0,0},{1,1,1,0,0,0,0,1},{1,1,1,0,0,0,1,0},{1,1,1,0,0,0,1,1},{1,1,1,0,0,1,0,0},{1,1,1,0,0,1,0,1},{1,1,1,0,0,1,1,0},{1,1,1,0,0,1,1,1},	//224~231
	{1,1,1,0,1,0,0,0},{1,1,1,0,1,0,0,1},{1,1,1,0,1,0,1,0},{1,1,1,0,1,0,1,1},{1,1,1,0,1,1,0,0},{1,1,1,0,1,1,0,1},{1,1,1,0,1,1,1,0},{1,1,1,0,1,1,1,1},	//232~239
	{1,1,1,1,0,0,0,0},{1,1,1,1,0,0,0,1},{1,1,1,1,0,0,1,0},{1,1,1,1,0,0,1,1},{1,1,1,1,0,1,0,0},{1,1,1,1,0,1,0,1},{1,1,1,1,0,1,1,0},{1,1,1,1,0,1,1,1},	//240~247
	{1,1,1,1,1,0,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,1,0,1,0},{1,1,1,1,1,0,1,1},{1,1,1,1,1,1,0,0},{1,1,1,1,1,1,0,1},{1,1,1,1,1,1,1,0},{1,1,1,1,1,1,1,1}		//248~255
};
// dissection function,Cut the data into ⌈InBytesBuFF_Length/256⌉ segments
int DissectionTheDatas(int InBytesBuFF_Length)
{
	int paragraphs = InBytesBuFF_Length / Ps;
	if(InBytesBuFF_Length > paragraphs * Ps){
		return paragraphs + 1;
	}else{
		return paragraphs;
	}
}
// Query 'RandomOfbitTable' table function
unsigned char QuerybitTable(int index, unsigned char bitSymbol)
{
	return RandomOfbitTable[ (index + bitSymbol) % 256 ] ^ bitSymbol;
};
// Query 'RandomOfUCharTable' table function
double QueryUCharTable(int index, unsigned char bitSymbol, double r, unsigned char OneKeytByte)
{
	return r - (double)RandomOfUCharTable[ (index + bitSymbol) % 256 ]/(100000.0 + OneKeytByte);
};
// Obtain a sequence Y and obtain a weighted coefficient---JIELINCODE Coefficient
double TheCOEofY(WJLCoder *coder, int partIndex, int paragraphs, unsigned char *Y, int Y_len){
	unsigned char tmpBit, tmpByte = 0;
	int i, j, Count0 = 0;
	double H = 0;
	// Number of statistical symbols 0
	for(i = 0; i < Y_len; ++i){
		tmpByte = 0x00;
		for(j = 0; j < 8; ++ j) {
			tmpByte <<= 1;
			tmpBit = QuerybitTable((i * 8 + j) % 256, bitOfByteTable[(int)Y[i]][j]);
			if(tmpBit == 0) {
				Count0 ++;
			}else{
				tmpByte |= tmpBit;
			}
		}
		Y[i] = tmpByte;
	}
	// Get the probability p0 of symbol 0 and the probability p1 of symbol 1
	coder->p0 = (double)Count0 / (double)(Y_len * 8.0);
	coder->p1 = 1.0 - coder->p0;
	// Binary sequences of all 0 or all 1 need to be preprocessed
	if(coder->p0 == 0.0){
		coder->p0 = 0.0000000001;
		coder->p1 = 1.0 - coder->p0;
	}else if(coder->p1 == 0.0){
		coder->p1 = 0.0000000001;
		coder->p0 = 1.0 - coder->p1;
	}
	// get the standard information entropy
	H = -coder->p0 * (log(coder->p0)/log(2.0))- coder->p1 * (log(coder->p1)/log(2.0));
	// get the Jielin code coefficient
	return pow( 2.0, H - ( ((double)coder->HashValueBuFF_Length) / (double)Y_len ));
}
// Output bytes to cache and weighted encoding
void OutPutByte(WJLCoder *coder, unsigned char ucByte)
{
	coder->HashValueBuFF[ coder->EOut_buff_loop % coder->HashValueBuFF_Length ] = (unsigned char)((unsigned int)coder->HashValueBuFF[ coder->EOut_buff_loop % coder->HashValueBuFF_Length ] + (unsigned int)ucByte);
	coder->EOut_buff_loop ++;
}
// Encode by JielinCeo
void Encode(WJLCoder *coder, unsigned char symbol)
{	
	unsigned int High = 0,i = 0;
	if (1 == symbol){// the Symbol 1
		coder->EFLow = coder->EFLow +  (unsigned int)((double)coder->EFRange * coder->p0);
		coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p1 * coder->JIELINCOE);
	}else{
		coder->EFRange = (unsigned int)((double)coder->EFRange * coder->p0 * coder->JIELINCOE);
	}
	while(coder->EFRange <= coder->RC_MIN_RANGE){
		High = coder->EFLow + coder->EFRange - 1;
		if(coder->EFFollow != 0) {
			if (High <= coder->RC_MAX_RANGE) {
				OutPutByte(coder, coder->EFDigits);
				for (i = 1; i <= coder->EFFollow - 1; ++i){
					OutPutByte(coder, 0xFF);
				}
				coder->EFFollow = 0;
				coder->EFLow = coder->EFLow + coder->RC_MAX_RANGE;
			} else if (coder->EFLow >= coder->RC_MAX_RANGE) {
				OutPutByte(coder, coder->EFDigits + 1);
				for (i = 1; i <= coder->EFFollow - 1; ++i){
					OutPutByte(coder, 0x00);
				}									
				coder->EFFollow = 0;
			} else {
				coder->EFFollow += 1;
				coder->EFLow = (coder->EFLow << 8) & (coder->RC_MAX_RANGE - 1);
				coder->EFRange = coder->EFRange << 8;
				continue;
			}
		}
		if  (((coder->EFLow ^ High) & (0xFF << coder->RC_SHIFT_BITS)) == 0) {
			OutPutByte(coder, (unsigned char)(coder->EFLow >> coder->RC_SHIFT_BITS));
		}else{
			coder->EFLow = coder->EFLow - coder->RC_MAX_RANGE;
			coder->EFDigits = coder->EFLow >> coder->RC_SHIFT_BITS;
			coder->EFFollow = 1;
		}
		coder->EFLow = ( ( (coder->EFLow << 8) & (coder->RC_MAX_RANGE - 1) ) | (coder->EFLow & coder->RC_MAX_RANGE) );
		coder->EFRange = coder->EFRange << 8;
	}
}
// Finish Encode by JielinCeo
void FinishEncode(WJLCoder *coder)
{
	int n = 0;
	if (coder->EFFollow != 0) {
		if (coder->EFLow < coder->RC_MAX_RANGE) {
			OutPutByte(coder, coder->EFDigits);
			for (n = 1; n <= coder->EFFollow - 1; n++) {
				OutPutByte(coder, 0xFF);
			}
		} else {
			OutPutByte(coder, coder->EFDigits + 1);
			for (n = 1; n <= coder->EFFollow - 1; n++) {
				OutPutByte(coder, 0x00);
			}
		}
	}
	coder->EFLow = coder->EFLow << 1;
	n = coder->RC_CODE_BITS + 1;
	do {
		n -= 8;
		OutPutByte(coder, (unsigned char)(coder->EFLow >> n));
	} while (!(n <= 0));
}
// Initialization WJLCoder
void InitializationWJLCoder(WJLCoder *coder)
{
	coder->RC_CODE_BITS = 31;
	coder->RC_SHIFT_BITS = coder->RC_CODE_BITS - 8;
	coder->RC_MAX_RANGE = 1 << coder->RC_CODE_BITS;
	coder->RC_MIN_RANGE = 1 << coder->RC_SHIFT_BITS;
	coder->p0 = 0.0;
	coder->p1 = 0.0;
	coder->JIELINCOE = 0.0;
	coder->EFLow = coder->RC_MAX_RANGE;
	coder->EFRange = coder->RC_MAX_RANGE;
	coder->EFDigits = 0;
	coder->EFFollow = 0;
	coder->EOut_buff_loop = 0;
	coder->HashValueBuFF_Length = 0;
}
// the main function
void WJLHA3(unsigned char *InBytesBuFF, int InBytesBuFF_Length, unsigned char *keytBuFF, int keytBuFF_Length, unsigned char *HashValueBuFF, int HashValueBuFF_Length)
{
	unsigned char *Y, *tempInbuff;
	int Y_len = Ps, i = 0, j = 0;
	unsigned int k = 0;
	int partIndex = 0, paragraphs = 0;
	WJLCoder *coder;
	double coe = 0.0;
	if(HashValueBuFF == 0){
		HashValueBuFF = (unsigned char *)malloc(HashValueBuFF_Length);
	}
	// Initialization WJLCoder Object
	coder = (WJLCoder *)malloc(sizeof(WJLCoder));
	Y = (unsigned char *)malloc(Y_len * sizeof(unsigned char));
	paragraphs = DissectionTheDatas(InBytesBuFF_Length);
	InitializationWJLCoder(coder);
	coder->HashValueBuFF_Length = HashValueBuFF_Length;
	coder->HashValueBuFF  = (unsigned char *)malloc(HashValueBuFF_Length);

	if(InBytesBuFF_Length < HashValueBuFF_Length){
		tempInbuff = (unsigned char *)malloc(HashValueBuFF_Length);
		memcpy(tempInbuff, InBytesBuFF, InBytesBuFF_Length);
		for(i = InBytesBuFF_Length; i < HashValueBuFF_Length; ++i){
			tempInbuff[i] = (unsigned char)(RandomOfUCharTable[i] + (InBytesBuFF[i % InBytesBuFF_Length] << 1) | 0x01 ) ^ (InBytesBuFF[i % InBytesBuFF_Length] + RandomOfbitTable[255 - i] + RandomOfUCharTable[i]);
		}
		InBytesBuFF_Length = HashValueBuFF_Length;
	}else{
		tempInbuff = InBytesBuFF;
	}

	if(keytBuFF_Length > InBytesBuFF_Length * 8){
		for(i = InBytesBuFF_Length * 8; i < keytBuFF_Length; ++i){
			keytBuFF[i % (InBytesBuFF_Length * 8)] = (unsigned char)(keytBuFF[i % (InBytesBuFF_Length * 8)] * keytBuFF[i]) ^ (keytBuFF[i] + keytBuFF[i % (InBytesBuFF_Length * 8)]);
		}
		keytBuFF_Length = InBytesBuFF_Length * 8;
	}

	// Segprocessing
	for(partIndex = 1; partIndex <= paragraphs; ++partIndex){
		if(partIndex == paragraphs){
			Y_len = InBytesBuFF_Length - (paragraphs - 1)* Ps;
		}
		memcpy(Y, tempInbuff + (partIndex - 1) * Ps, Y_len);
		// Get COE of Y
		coe = TheCOEofY(coder, partIndex, paragraphs, Y, Y_len);
		// Encode each bits
		for(i = 0; i < Y_len; ++i){
			for(j = 0; j < 8; ++j){
				coder->JIELINCOE = QueryUCharTable(i, bitOfByteTable[(int)Y[i]][j], coe, keytBuFF[ k % keytBuFF_Length ]);
				Encode(coder, bitOfByteTable[(int)Y[i]][j]);
				k ++;
			}
		}
	}
	FinishEncode(coder);
	memcpy(HashValueBuFF, coder->HashValueBuFF, HashValueBuFF_Length);
	// Free memory
	free(Y);
	free(tempInbuff);
	free(coder->HashValueBuFF);
	free(coder);
}
