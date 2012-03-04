#include "stdafx.h"
#include "WindowsAudioDevice.h"
#include "GdxRuntimeException.h"

WindowsAudioDevice::WindowsAudioDevice(int samplingRate, bool isMono)
	: m_mono(isMono)
{
	WAVEFORMATEX wfx;
	waveBlocks = allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount = BLOCK_COUNT;
	waveCurrentBlock= 0;
	InitializeCriticalSection(&waveCriticalSection);

	/*
	* set up the WAVEFORMATEX structure.
	*/
	wfx.nSamplesPerSec = samplingRate; /* sample rate */
	wfx.wBitsPerSample = 16; /* sample size */
	wfx.nChannels= isMono? 1: 2; /* channels*/
	wfx.cbSize = 0; /* size of _extra_ info */
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nBlockAlign = (wfx.wBitsPerSample * wfx.nChannels) >> 3;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	/*
	* try to open the default wave device. WAVE_MAPPER is
	* a constant defined in mmsystem.h, it always points to the
	* default wave device on the system (some people have 2 or
	* more sound cards).
	*/
	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc, (DWORD_PTR)this, CALLBACK_FUNCTION) 
		!= MMSYSERR_NOERROR) 
	{
			GdxRuntimeException("Unable to open wave mapper device");
	}
}

WindowsAudioDevice::~WindowsAudioDevice()
{
	/*
	* wait for all blocks to complete
	*/
	while(waveFreeBlockCount < BLOCK_COUNT)
		Sleep(10);

	/*
	* unprepare any blocks that are still prepared
	*/
	for(int i = 0; i < waveFreeBlockCount; i++) 
		if(waveBlocks[i].dwFlags & WHDR_PREPARED)
			waveOutUnprepareHeader(hWaveOut, &waveBlocks[i], sizeof(WAVEHDR));
	DeleteCriticalSection(&waveCriticalSection);
	freeBlocks(waveBlocks);
	waveOutClose(hWaveOut);
}

/** @return whether this AudioDevice is in mono or stereo mode. */
bool WindowsAudioDevice::isMono()
{
	return m_mono;
}

/** Writes the array of 16-bit signed PCM samples to the audio device and blocks until they have been processed.
*
* @param samples The samples.
* @param numSamples the number of samples to write to the device */
void WindowsAudioDevice::writeSamples(short samples[], int numSamples)
{
	writeAudio(hWaveOut, (char*)samples, numSamples * 2);
}


/** Writes the array of float PCM samples to the audio device and blocks until they have been processed.
*
* @param samples The samples.
* @param numSamples the number of samples to write to the device */
void WindowsAudioDevice::writeSamples(float samples[], int numSamples)
{
	throw GdxRuntimeException("not implemented yet");
}

/** @return the latency in samples. */
int WindowsAudioDevice::getLatency()
{
	throw GdxRuntimeException("not implemented yet");
}

/** Frees all resources associated with this AudioDevice. Needs to be called when the device is no longer needed. */
void WindowsAudioDevice::dispose()
{
}

WAVEHDR* WindowsAudioDevice::allocateBlocks(int size, int count)
{
	char* buffer;
	int i;
	WAVEHDR* blocks;
	DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;
	/*
	* allocate memory for the entire set in one go
	*/
	if((buffer = (char*)HeapAlloc(
		GetProcessHeap(), 
		HEAP_ZERO_MEMORY, 
		totalBufferSize
		)) == NULL) {
			fprintf(stderr, "Memory allocation error\n");
			ExitProcess(1);
	}
	/*
	* and set up the pointers to each bit
	*/
	blocks = (WAVEHDR*)buffer;
	buffer += sizeof(WAVEHDR) * count;
	for(i = 0; i < count; i++) {
		blocks[i].dwBufferLength = size;
		blocks[i].lpData = buffer;
		buffer += size;
	}
	return blocks;
}
void WindowsAudioDevice::freeBlocks(WAVEHDR* blockArray)
{
	HeapFree(GetProcessHeap(), 0, blockArray);
}

void CALLBACK WindowsAudioDevice::waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1,DWORD dwParam2)
{
	WindowsAudioDevice* pDevice = (WindowsAudioDevice*)dwInstance;
	/*
	* pointer to free block counter
	*/
	int* freeBlockCounter = &(pDevice->waveFreeBlockCount);
	/*
	* ignore calls that occur due to openining and closing the
	* device.
	*/
	if(uMsg == WOM_DONE)
	{
		EnterCriticalSection(&pDevice->waveCriticalSection);
		(*freeBlockCounter)++;
		LeaveCriticalSection(&pDevice->waveCriticalSection);
	}
}

void WindowsAudioDevice::writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size)
{
	WAVEHDR* current;
	int remain;
	current = &waveBlocks[waveCurrentBlock];
	while(size > 0) 
	{
		/* 
		* first make sure the header we're going to use is unprepared
		*/
		if(current->dwFlags & WHDR_PREPARED) 
			waveOutUnprepareHeader(hWaveOut, current, sizeof(WAVEHDR));
		if(size < (int)(BLOCK_SIZE - current->dwUser)) 
		{
			memcpy(current->lpData + current->dwUser, data, size);
			current->dwUser += size;
			break;
		}
		remain = BLOCK_SIZE - current->dwUser;
		memcpy(current->lpData + current->dwUser, data, remain);
		size -= remain;
		data += remain;
		current->dwBufferLength = BLOCK_SIZE;
		waveOutPrepareHeader(hWaveOut, current, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, current, sizeof(WAVEHDR));
		EnterCriticalSection(&waveCriticalSection);
		waveFreeBlockCount--;
		LeaveCriticalSection(&waveCriticalSection);
		/*
		* wait for a block to become free
		*/
		while(!waveFreeBlockCount)
			Sleep(10);
		/*
		* point to the next block
		*/
		waveCurrentBlock++;
		waveCurrentBlock %= BLOCK_COUNT;
		current = &waveBlocks[waveCurrentBlock];
		current->dwUser = 0;
	}
}
