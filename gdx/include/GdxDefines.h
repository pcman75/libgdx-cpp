#pragma once

#if defined (__WIN32__)
#ifdef GDX_EXPORTS
  #define GdxDllImportExport __declspec(dllexport)
#else
  #define GdxDllImportExport __declspec(dllimport)
#endif
#else
	#define GdxDllImportExport
#endif
