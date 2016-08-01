#pragma once

#include "fl/Common.h"
#include "fl/String.h"

namespace fl {

	class FileSystem
	{
	public:
		static bool FileExists(const String& path);
		static int GetFileSize(const String& path);

		static byte* ReadFile(const String& path);
		static bool ReadFile(const String& path, void* buffer, long long size = -1);
		static String ReadTextFile(const String& path);

		static bool WriteFile(const String& path, byte* buffer);
		static bool WriteTextFile(const String& path, const String& text);
	};

}