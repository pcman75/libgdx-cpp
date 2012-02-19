#pragma once

#if defined (WIN32)
#ifdef GDXTESTS_EXPORTS
  #define GdxTestsDllImportExport __declspec(dllexport)
#else
  #define GdxTestsDllImportExport __declspec(dllimport)
#endif
#else
	#define GdxTestsDllImportExport
#endif
