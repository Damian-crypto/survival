#include "corepch.h"
#include "file_manager.h"
#include "logger.h"

#include <Windows.h>
#include <commdlg.h>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

bool zeus::FileManager::FileExists(const std::string& name)
{
	std::ifstream file(name);

	return file.good();
}

std::string zeus::FileManager::ReadFile(const std::string& name)
{
	std::ifstream file(name);
	std::stringstream buffer;

	if (file && file.is_open())
	{
		buffer << file.rdbuf();
		file.close();
	}
	else
	{
		std::string error_message = "The file specified cannot open \"" + name + "\"!";
		LOG(Error, error_message.c_str());
	}

	return buffer.str();
}

void zeus::FileManager::ReadBinaryFile(const std::string& name, char* buffer)
{
	std::ifstream file(name, std::ios::binary);

	if (file && file.is_open())
	{
		// Find the size of the file
		file.seekg(0, std::ios::end);
		std::streampos filesize = file.tellg();
		file.seekg(0, std::ios::beg);

		// Recreate the buffer
		buffer = new char[filesize];

		// Read the file content into the buffer
		file.read(buffer, filesize);

		file.close();
	}
	else
	{
		std::string error_message = "The file specified cannot open \"" + name + "\"!";
		LOG(Error, error_message.c_str());
	}
}

std::string zeus::FileManager::OpenFileDialog(const wchar_t* filter, void* native_window)
{
#ifdef _WIN32
	// Common dialog box structure
	OPENFILENAME ofn;
	WCHAR szFile[260] = { 0 };
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)native_window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrTitle = L"Open File";
	// OFN_NOCHANGEDIR = don't reset directory after a file in selected
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileName(&ofn) == TRUE)
		return (const char*)ofn.lpstrFile;
#else
	LOG(Error, "Currently engine does only support Windows file dialogs");
#endif
	return std::string();
}

std::string zeus::FileManager::SaveFileDialog(const wchar_t* filter, void* native_window)
{
#ifdef _WIN32
	// Common dialog box structure
	OPENFILENAME ofn;
	WCHAR szFile[260] = { 0 };
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)native_window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	// OFN_NOCHANGEDIR = don't reset directory after a file in selected
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	ofn.lpstrTitle = L"Save File";
	if (GetSaveFileName(&ofn) == TRUE)
		return (const char*)ofn.lpstrFile;
#else
	LOG(Error, "Currently engine does only support Windows file dialogs");
#endif
	return std::string();
}
