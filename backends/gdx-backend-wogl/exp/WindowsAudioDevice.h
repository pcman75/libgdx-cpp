/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#pragma once


#include "AudioDevice.h"

/** Encapsulates an audio device in 44.1khz mono or stereo mode. Use the {@link #writeSamples(float[], int, int)} and
 * {@link #writeSamples(short[], int, int)} methods to write float or 16-bit signed short PCM data directly to the audio device.
 * Stereo samples are interleaved in the order left channel sample, right channel sample. The {@link #dispose()} method must be
 * called when this AudioDevice is no longer needed.
 *
 * implementation based on http://www.planet-source-code.com/vb/scripts/ShowCode.asp?txtCodeId=4422&lngWId=3 article
 */
class WindowsAudioDevice :
	public AudioDevice
{
private:
	/*
	* some good values for block size and count
	*/
	static const int BLOCK_SIZE = 8192;
	static const int BLOCK_COUNT = 20;

	HWAVEOUT hWaveOut; /* device handle */

	CRITICAL_SECTION waveCriticalSection;
	WAVEHDR* waveBlocks;
	int waveFreeBlockCount;
	int waveCurrentBlock;
	bool m_mono;
	char* m_bytesBuf;
	int m_bytesBufLength;
public:
	WindowsAudioDevice(int samplingRate, bool isMono);
	virtual ~WindowsAudioDevice();

	/** @return whether this AudioDevice is in mono or stereo mode. */
	virtual bool isMono();

	/** Writes the array of 16-bit signed PCM samples to the audio device and blocks until they have been processed.
	 *
	 * @param samples The samples.
	 * @param numSamples the number of samples to write to the device */
	virtual void writeSamples(short samples[], int numSamples);

	/** Writes the array of float PCM samples to the audio device and blocks until they have been processed.
	 *
	 * @param samples The samples.
	 * @param numSamples the number of samples to write to the device */
	virtual void writeSamples(float samples[], int numSamples);

	/** @return the latency in samples. */
	virtual int getLatency();

	/** Frees all resources associated with this AudioDevice. Needs to be called when the device is no longer needed. */
	virtual void dispose();

private:
	static void CALLBACK waveOutProc(HWAVEOUT, UINT, DWORD, DWORD, DWORD);
	WAVEHDR* allocateBlocks(int size, int count);
	void freeBlocks(WAVEHDR* blockArray);
	void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size);
};
