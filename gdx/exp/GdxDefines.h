#pragma once

#ifdef GDX_EXPORTS
  #define GdxDllImportExport __declspec(dllexport)
#else
  #define GdxDllImportExport __declspec(dllimport)
#endif

