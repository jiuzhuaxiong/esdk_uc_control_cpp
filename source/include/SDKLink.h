#pragma once

#ifdef ESDK_EXPORTS
  #define ESDK_API __declspec(dllexport)
#else 
  #define ESDK_API __declspec(dllimport)
#endif

