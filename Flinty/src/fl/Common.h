#pragma once

#include "fl/Types.h"

// TODO: Move to precompiled header
#include <iostream>

// Common data structures
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Disable warnings
#pragma warning(disable : 4251)

// Some typedefs to rename C++'s questionable names
template<typename T> using HashSet = std::unordered_set<T>;
template<typename K, typename V> using HashMap = std::unordered_map<K, V>;

#ifdef FL_PLATFORM_WINDOWS
	#ifdef FL_CORE_DLL
		#pragma message("Exporting...")
		#define FL_API __declspec(dllexport)
	#else
		#pragma message("Importing...")
		#define FL_API __declspec(dllimport)
	#endif
#else
	#define FL_API
#endif

namespace fl {
	extern void GLClearError();
	extern bool GLLogCall(const char* function, const char* file, int line);
}

#ifdef FL_DEBUG
	#define GLCall(x) fl::GLClearError();\
		x; \
		if (!fl::GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
	#define GLCall(x) x
#endif

#ifdef FL_DEBUG
	#define FL_ASSERT(x, ...) \
		if (!(x)) {\
			std::cout << "*************************" << std::endl; \
			std::cout << "    ASSERTION FAILED!    " << std::endl; \
			std::cout << "*************************" << std::endl; \
			std::cout << __FILE__ << ": " << __LINE__ << std::endl; \
			std::cout << "Condition: " << #x << std::endl; \
			__debugbreak(); \
		}
#else
	#define FL_ASSERT(x, ...)
#endif

#define BIT(x) 1 << x