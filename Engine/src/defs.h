#pragma once

// DLL Import / Export
#ifdef ENG_DLL_EXPORT
  #define ENG_API __declspec(dllexport)
#else
  #define ENG_API __declspec(dllimport)
#endif