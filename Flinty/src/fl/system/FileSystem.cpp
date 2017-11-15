#include "FileSystem.h"

#include <algorithm>

namespace fl {

	bool FileSystem::FileExists(const String& path)
	{
		return false;
	}

	int FileSystem::GetFileSize(const String& path)
	{
		return 0;
	}

	byte* FileSystem::ReadFile(const String& path)
	{
		FILE* file = fopen(path.c_str(), "rb");
		if (file == nullptr)
			FL_ASSERT(file, "Could not open file '", filepath, "'!");

		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		FL_ASSERT(length < 100 * 1024 * 1024);
		byte* result = new byte[length];
		fread(result, 1, length, file);
		fclose(file);
		return result;
	}

	bool FileSystem::ReadFile(const String& path, void* buffer, long long size)
	{
		return false;
	}

	String FileSystem::ReadTextFile(const String& path)
	{
		FILE* file = fopen(path.c_str(), "rb");
		if (file == nullptr)
			FL_ASSERT(file, "Could not open file '", filepath, "'!");

		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		FL_ASSERT(length < 100 * 1024 * 1024);
		String result(length, 0);
		fseek(file, 0, SEEK_SET);
		fread(&result[0], 1, length, file);
		fclose(file);

		// Strip carriage returns
		result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
		return result;
	}

	bool FileSystem::WriteFile(const String& path, byte* buffer)
	{
		return false;
	}

	bool FileSystem::WriteTextFile(const String& path, const String& text)
	{
		return false;
	}

}