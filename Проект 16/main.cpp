#include "wav.h"
using namespace std;
int main(int argc, char** argv)
{
	WAVE_HEADER* wav_hdr1 = new WAVE_HEADER;
	DATA_CHUNK* dt1 = new DATA_CHUNK;
	WAVE_HEADER* wav_hdr2 = new WAVE_HEADER;
	DATA_CHUNK* dt2 = new DATA_CHUNK;
	/*short* samples1 = get_wav(wav_hdr1, dt1, "in1.wav");
	short* samples2 = get_wav(wav_hdr2, dt2, "in2.wav");
	set_wav_difference(wav_hdr1, wav_hdr2, dt1, dt2, samples1, samples2, "out.wav");
	set_wav_half(wav_hdr1, wav_hdr2, dt1, dt2, samples1, samples2, "out.wav");*/
	short* samples1 = get_wav(wav_hdr1, dt1, argv[1]);
	short* samples2 = get_wav(wav_hdr2, dt2, argv[2]);
	//set_wav_difference(wav_hdr1, wav_hdr2, dt1, dt2, samples1, samples2, argv[3]);
	set_wav_half(wav_hdr1, wav_hdr2, dt1, dt2, samples1, samples2, argv[3]);
	delete wav_hdr1;
	delete dt1;
	delete[] samples1;
	delete wav_hdr2;
	delete dt2;
	delete[] samples2;
	return 0;
}