#include "wav.h"
using namespace std;
short* get_wav(WAVE_HEADER* wav_hdr, DATA_CHUNK* dt, char* filename)
{
	ifstream fin(filename, ios_base::binary | ios_base::in);
	if (fin.fail())
	{
		cout << "Error input." << endl;
		fin.close();
		return NULL;
	}
	else
	{
		fin.read((char*)&wav_hdr->riff, sizeof(wav_hdr->riff));
		fin.read((char*)&wav_hdr->riffsize, sizeof(wav_hdr->riffsize));
		fin.read((char*)&wav_hdr->wawefmt, sizeof(wav_hdr->wawefmt));
		fin.read((char*)&wav_hdr->fmtsize, sizeof(wav_hdr->riff));
		fin.read((char*)&wav_hdr->wFormatTag, sizeof(wav_hdr->wFormatTag));
		fin.read((char*)&wav_hdr->nChannels, sizeof(wav_hdr->nChannels));
		fin.read((char*)&wav_hdr->nSamplesPerSec, sizeof(wav_hdr->nSamplesPerSec));
		fin.read((char*)&wav_hdr->nAvgBytesPerSec, sizeof(wav_hdr->nAvgBytesPerSec));
		fin.read((char*)&wav_hdr->nBlockAlign, sizeof(wav_hdr->nBlockAlign));
		fin.read((char*)&wav_hdr->wBitsPerSample, sizeof(wav_hdr->wBitsPerSample));
		fin.read((char*)&dt->data, sizeof(dt->data));
		fin.read((char*)&dt->datasize, sizeof(dt->datasize));
		unsigned char* samples = new unsigned char[dt->datasize];
		fin.seekg(ios_base::cur);
		for (DWORD i = 0; i < dt->datasize; i++)
		{
			fin.read((char*)&samples[i], sizeof(char));
		}
		short* data = new short[dt->datasize / 2];
		for (DWORD i = 0; i < dt->datasize / 2; i++)
		{
			int tmp1 = samples[2 * i];
			int tmp2 = samples[2 * i + 1];
			data[i] = ((tmp1 << 8) | tmp2);
		}
		delete[] samples;
		fin.close();
		return data;
	}
}
void set_wav_difference(WAVE_HEADER* wav_hdr1, WAVE_HEADER* wav_hdr2, DATA_CHUNK* dt1, DATA_CHUNK* dt2, short* data1, short* data2, char* filename)
{
	ofstream fout(filename, ios_base::binary | ios_base::out);
	if (fout.fail())
	{
		cout << "Error output." << endl;
	}
	else
	{
		float duration1 = 1.f * dt1->datasize / (wav_hdr1->wBitsPerSample / 8) / wav_hdr1->nChannels / wav_hdr1->nSamplesPerSec;
		float duration2 = 1.f * dt2->datasize / (wav_hdr2->wBitsPerSample / 8) / wav_hdr2->nChannels / wav_hdr2->nSamplesPerSec;
		if (duration1 < duration2)
		{
			fout.write((char*)&wav_hdr1->riff, sizeof(wav_hdr1->riff));
			fout.write((char*)&wav_hdr1->riffsize, sizeof(wav_hdr1->riffsize));
			fout.write((char*)&wav_hdr1->wawefmt, sizeof(wav_hdr1->wawefmt));
			fout.write((char*)&wav_hdr1->fmtsize, sizeof(wav_hdr1->riff));
			fout.write((char*)&wav_hdr1->wFormatTag, sizeof(wav_hdr1->wFormatTag));
			fout.write((char*)&wav_hdr1->nChannels, sizeof(wav_hdr1->nChannels));
			fout.write((char*)&wav_hdr1->nSamplesPerSec, sizeof(wav_hdr1->nSamplesPerSec));
			fout.write((char*)&wav_hdr1->nAvgBytesPerSec, sizeof(wav_hdr1->nAvgBytesPerSec));
			fout.write((char*)&wav_hdr1->nBlockAlign, sizeof(wav_hdr1->nBlockAlign));
			fout.write((char*)&wav_hdr1->wBitsPerSample, sizeof(wav_hdr1->wBitsPerSample));
			fout.write((char*)&dt1->data, sizeof(dt1->data));
			fout.write((char*)&dt1->datasize, sizeof(dt1->datasize));
			for (DWORD i = 0; i < dt1->datasize / 2; i++)
			{
				int tmp = data1[i] - data2[i];
				if (tmp < -32767)
				{
					tmp = -32767;
				}
				if (tmp > 32767)
				{
					tmp = 32767;
				}
				data1[i] = tmp;
				fout.write((char*)&data1[i], sizeof(short));
			}
		}
		else
		{
			fout.write((char*)&wav_hdr2->riff, sizeof(wav_hdr2->riff));
			fout.write((char*)&wav_hdr2->riffsize, sizeof(wav_hdr2->riffsize));
			fout.write((char*)&wav_hdr2->wawefmt, sizeof(wav_hdr2->wawefmt));
			fout.write((char*)&wav_hdr2->fmtsize, sizeof(wav_hdr2->riff));
			fout.write((char*)&wav_hdr2->wFormatTag, sizeof(wav_hdr2->wFormatTag));
			fout.write((char*)&wav_hdr2->nChannels, sizeof(wav_hdr2->nChannels));
			fout.write((char*)&wav_hdr2->nSamplesPerSec, sizeof(wav_hdr2->nSamplesPerSec));
			fout.write((char*)&wav_hdr2->nAvgBytesPerSec, sizeof(wav_hdr2->nAvgBytesPerSec));
			fout.write((char*)&wav_hdr2->nBlockAlign, sizeof(wav_hdr2->nBlockAlign));
			fout.write((char*)&wav_hdr2->wBitsPerSample, sizeof(wav_hdr2->wBitsPerSample));
			fout.write((char*)&dt2->data, sizeof(dt2->data));
			fout.write((char*)&dt2->datasize, sizeof(dt2->datasize));
			for (DWORD i = 0; i < dt2->datasize / 2; i++)
			{
				int tmp = data1[i] - data2[i];
				if (tmp < -32767)
				{
					tmp = -32767;
				}
				if (tmp > 32767)
				{
					tmp = 32767;
				}
				data1[i] = tmp;
				fout.write((char*)&data1[i], sizeof(short));
			}
		}
	}
	fout.close();
}
void set_wav_half(WAVE_HEADER* wav_hdr1, WAVE_HEADER* wav_hdr2, DATA_CHUNK* dt1, DATA_CHUNK* dt2, short* data1, short* data2, char* filename)
{
	ofstream fout(filename, ios_base::binary | ios_base::out);
	if (fout.fail())
	{
		cout << "Error output." << endl;
	}
	else
	{
		fout.write((char*)&wav_hdr1->riff, sizeof(wav_hdr1->riff));
		fout.write((char*)&wav_hdr1->riffsize, sizeof(wav_hdr1->riffsize));
		fout.write((char*)&wav_hdr1->wawefmt, sizeof(wav_hdr1->wawefmt));
		fout.write((char*)&wav_hdr1->fmtsize, sizeof(wav_hdr1->riff));
		fout.write((char*)&wav_hdr1->wFormatTag, sizeof(wav_hdr1->wFormatTag));
		fout.write((char*)&wav_hdr1->nChannels, sizeof(wav_hdr1->nChannels));
		fout.write((char*)&wav_hdr1->nSamplesPerSec, sizeof(wav_hdr1->nSamplesPerSec));
		fout.write((char*)&wav_hdr1->nAvgBytesPerSec, sizeof(wav_hdr1->nAvgBytesPerSec));
		fout.write((char*)&wav_hdr1->nBlockAlign, sizeof(wav_hdr1->nBlockAlign));
		fout.write((char*)&wav_hdr1->wBitsPerSample, sizeof(wav_hdr1->wBitsPerSample));
		fout.write((char*)&dt1->data, sizeof(dt1->data));
		DWORD temp = dt1->datasize / 2;
		temp += dt2->datasize / 2;
		fout.write((char*)&temp, sizeof(temp));
		for (DWORD i = 0; i < dt1->datasize / 4; i++)
		{
			fout.write((char*)&data1[i], sizeof(short));
		}
		for (DWORD i = dt2->datasize / 4; i < dt2->datasize / 2; i++)
		{
			fout.write((char*)&data2[i], sizeof(short));
		}
	}
	fout.close();;
}