#pragma once

#if defined (WIN32)
#ifdef GDXAUDIO_EXPORTS
  #define GdxAudioDllImportExport __declspec(dllexport)
#else
  #define GdxAudioDllImportExport __declspec(dllimport)
#endif
#else
	#define GdxAudioDllImportExport 
#endif
