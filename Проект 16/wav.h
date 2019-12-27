#ifndef WAV_H
#define WAV_H
#include <iostream>
#include <fstream>
#include <windows.h>
typedef struct
{
	BYTE riff[4];
	DWORD riffsize;
	BYTE wawefmt[8];
	DWORD fmtsize;
	WORD wFormatTag;
	WORD nChannels;
	DWORD nSamplesPerSec;
	DWORD nAvgBytesPerSec;
	WORD nBlockAlign;
	SHORT wBitsPerSample;
} WAVE_HEADER;
typedef struct
{
	BYTE data[4];
	DWORD datasize;
} DATA_CHUNK;
short* get_wav(WAVE_HEADER* wav_hdr, DATA_CHUNK* dt, char* filename);
void set_wav_difference(WAVE_HEADER* wav_hdr1, WAVE_HEADER* wav_hdr2, DATA_CHUNK* dt1, DATA_CHUNK* dt2, short* data1, short* data2, char* filename);
void set_wav_half(WAVE_HEADER* wav_hdr1, WAVE_HEADER* wav_hdr2, DATA_CHUNK* dt1, DATA_CHUNK* dt2, short* data1, short* data2, char* filename);
#endif