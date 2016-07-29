#pragma once

#include <string>
typedef std::string String;
typedef unsigned int uint;

#ifdef FL_PLATFORM_WINDOWS
	#ifdef FL_CORE_DLL
		#define FL_API __declspec(dllexport)
	#else
		#define FL_API __declspec(dllimport)
	#endif
#else
	#define FL_API
#endif