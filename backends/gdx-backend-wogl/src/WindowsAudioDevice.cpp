#include "stdafx.h"
#include "WindowsAudioDevice.h"
#include "GdxRuntimeException.h"

WindowsAudioDevice::~WindowsAudioDevice()
{
}

/** @return whether this AudioDevice is in mono or stereo mode. */
bool WindowsAudioDevice::isMono()
{
	throw GdxRuntimeException("not implemented yet");
}

/** Writes the array of 16-bit signed PCM samples to the audio device and blocks until they have been processed.
*
* @param samples The samples.
* @param numSamples the number of samples to write to the device */
void WindowsAudioDevice::writeSamples(short samples[], int numSamples)
{
	throw GdxRuntimeException("not implemented yet");
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
	throw GdxRuntimeException("not implemented yet");
}
