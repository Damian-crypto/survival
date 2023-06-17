#pragma once

#include <string>
#include <functional>
#include <vector>

struct GLFWwindow;

namespace zeus
{
	struct MenuItem
	{
		std::string ItemName;
		std::string ShortCut;
		std::function<bool(void)> Action;
	};

	class ImGUI
	{
	private:
		GLFWwindow* m_NativeWindow;
		std::vector<MenuItem> m_MenuItems;
		bool m_DockingEnabled = true;
		static bool m_ImGuiInitialized;

	public:
		void Init(bool docked);
		void Begin();
		void End();
		void Destroy();
		bool IsKeyPressed(uint32_t keycode);

		std::string ShowOpenFileDialog();
		std::string ShowSaveFileDialog();

		void AddMenuItem(const MenuItem& item);
		void EnableDocking(bool enabled);

		/// <summary>
		/// Check whether ImGui is blocking events.
		/// </summary>
		/// <returns>true if ImGui is blocking events.</returns>
		static bool IsBlocking();
	};
}
