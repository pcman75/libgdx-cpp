#pragma once

#ifdef GDXBACKENDWOGL_EXPORTS
  #define WOGLDllImportExport __declspec(dllexport)
#else
  #define WOGLDllImportExport __declspec(dllimport)
#endif

