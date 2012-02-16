#pragma once

#if defined (WIN32)
#ifdef GDX_EXPORTS
  #define GdxDllImportExport __declspec(dllexport)
#else
  #define GdxDllImportExport __declspec(dllimport)
#endif
#else
	#define GdxDllImportExport
#endif
