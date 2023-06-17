#pragma once

#include <string>
#include <memory>

#include "layer_queue.h"
#include "window/window.h"
#include "glm/glm.hpp"
#include "util/imgui_ui.h"

namespace zeus
{
	struct ApplicationProperties
	{
		std::string Title{ "" };
		uint32_t Width{ 1280 };
		uint32_t Height{ 720 };
		bool Docked{ true };
		bool Resizable { true };
	};

	class Application
	{
	private:
		// Private fields
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<ImGUI> m_ImGui;
		ApplicationProperties m_Properties;
		LayerQueue m_LayerQueue;
		float m_DeltaTime = 0.0f;
		bool m_Running = false;

		// Static fields
		static Application* s_Instance;

	public:
		//Application();
		Application(ApplicationProperties props);
		~Application();

		/// <summary>
		/// Returns the active instance of the application.
		/// </summary>
		/// <returns>current application pointer</returns>
		static Application* GetInstance();

		/// <summary>
		/// All tools will be initialized here
		/// </summary>
		void Init();

		/// <summary>
		/// Start the main loop
		/// </summary>
		void Run();

		/// <summary>
		/// Stop the main loop
		/// </summary>
		void Stop();

		/// <summary>
		/// This will execute all evt type events in all layers
		/// </summary>
		/// <param name="evt">specific event to be called</param>
		void OnEvent(Event& evt);

		/// <summary>
		/// Pushes a layer into the layer queue of the application and the layer will be executed in every frame.
		/// </summary>
		/// <param name="layer">pointer to the layer</param>
		void PushLayer(Layer* layer);

		/// <summary>
		/// Enable vertical synchronization of the engine.
		/// This will limit the frames generated at a second to 60 FPS(default).
		/// </summary>
		/// <param name="enabled">is vsync enabled?</param>
		void SetVSync(bool enabled = true);

		/// <summary>
		/// Returns the active window
		/// </summary>
		/// <returns>platform agnostic current window will be returned.</returns>
		std::shared_ptr<Window> GetWindow();

		/// <summary>
		/// Engine's immediate mode custom gui handler will be returned
		/// </summary>
		/// <returns>ImGui based custom class will be returned.</returns>
		std::shared_ptr<ImGUI> GetUI();

		/// <summary>
		/// Engine's current framerate will be returned.
		/// Default should be 60 FPS.
		/// </summary>
		/// <returns>current framerate of the engine will be returned</returns>
		int GetFramerate() const;

		/// <summary>
		/// Current application properties will be returned.
		/// </summary>
		/// <returns>returns a struct of application properties.</returns>
		ApplicationProperties& GetApplicationProperties();
	};
}
