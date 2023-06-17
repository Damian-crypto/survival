#pragma once

#include <string>

namespace zeus
{
	class FileManager
	{
	public:
		FileManager() = delete;

		/// <summary>
		/// Returns true if the specified file exists.
		/// </summary>
		/// <param name="name">Absolute path of the file</param>
		/// <returns>true if the file exists otherwise false</returns>
		static bool FileExists(const std::string& name);

		/// <summary>
		/// Read the entire file and return it as a single string.
		/// </summary>
		/// <param name="name">Absolute path of the file</param>
		/// <returns>File content as a string</returns>
		static std::string ReadFile(const std::string& name);

		/// <summary>
		/// Read a binary. IMPORTANT! THIS FUNCTION WILL CREATE A BUFFER INTERNALLY
		/// PROGRAMMER HAS TO CLEAR THE BUFFER ALLOCATED.
		/// </summary>
		/// <param name="name">Absolute path of the file</param>
		/// <param name="buffer">buffer pointer</param>
		static void ReadBinaryFile(const std::string& name, char* buffer);

		static std::string OpenFileDialog(const wchar_t* filter, void* native_window);

		static std::string SaveFileDialog(const wchar_t* filter, void* native_window);
	};
}
