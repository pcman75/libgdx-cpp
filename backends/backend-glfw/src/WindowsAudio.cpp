#include "stdafx.h"
#include "WindowsAudio.h"
#include "WindowsAudioDevice.h"
#include "GdxMusic.h"
#include "GdxSound.h"

/** Creates a new {@link AudioDevice} either in mono or stereo mode. The AudioDevice has to be disposed via its
* {@link AudioDevice#dispose()} method when it is no longer used.
*
* @param samplingRate the sampling rate.
* @param isMono whether the AudioDevice should be in mono or stereo mode
* @return the AudioDevice
*
* @throws GdxRuntimeException in case the device could not be created */
AudioDevice* WindowsAudio::newAudioDevice(int samplingRate, bool isMono)
{
	return new WindowsAudioDevice(samplingRate, isMono);
}

/** Creates a new {@link AudioRecorder}. The AudioRecorder has to be disposed after it is no longer used.
*
* @param samplingRate the sampling rate in Herz
* @param isMono whether the recorder records in mono or stereo
* @return the AudioRecorder
*
* @throws GdxRuntimeException in case the recorder could not be created */
AudioRecorder* WindowsAudio::newAudioRecorder(int samplingRate, bool isMono)
{
	return NULL;
}

/** <p>
* Creates a new {@link Sound} which is used to play back audio effects such as gun shots or explosions. The Sound's audio data
* is retrieved from the file specified via the {@link FileHandle}. Note that the complete audio data is loaded into RAM. You
* should therefore not load big audio files with this methods. The current upper limit for decoded audio is 1 MB.
* </p>
*
* <p>
* Currently supported formats are WAV, MP3 and OGG.
* </p>
*
* <p>
* The Sound has to be disposed if it is no longer used via the {@link Sound#dispose()} method.
* </p>
*
* @return the new Sound
* @throws GdxRuntimeException in case the sound could not be loaded */
Sound* WindowsAudio::newSound(const FileHandle& fileHandle)
{
	return new GdxSound();
}

/** Creates a new {@link Music} instance which is used to play back a music stream from a file. Currently supported formats are
* WAV, MP3 and OGG. The Music instance has to be disposed if it is no longer used via the {@link Music#dispose()} method.
* Music instances are automatically paused when {@link ApplicationListener#pause()} is called and resumed when
* {@link ApplicationListener#resume()} is called.
*
* @param file the FileHandle
* @return the new Music or null if the Music could not be loaded
* @throws GdxRuntimeException in case the music could not be loaded */
Music* WindowsAudio::newMusic(const FileHandle& file)
{
	//TODO:
	return new GdxMusic();
}

