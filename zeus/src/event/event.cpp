#include "corepch.h"
#include "event.h"
#include "util/imgui_ui.h"
#include "util/logger.h"

namespace zeus
{
	Event::Event()
	{
	}

	Event::Event(EventType& type)
		: m_Type(type)
	{
	}

	EventType Event::GetType()
	{
		return m_Type;
	}

	EventDispatcher::EventDispatcher(Event& evt)
		: m_Event(evt)
	{
	}

	/// <summary>
	/// This will dispatch the specified function for handle.
	/// </summary>
	/// <param name="type">Type of the event (MouseEvent, KeyboardEvent, etc.)</param>
	/// <param name="func">The function to be handled (will be executed).</param>
	/// <returns>true if the provided function handled successfully otherwise false.</returns>
	bool EventDispatcher::Dispatch(EventType type, std::function<bool()>& func)
	{
		// If ImGui is not blocking the events process it by application itself
		if (!ImGUI::IsBlocking())
		{
			// This event type checking is done to stop repeating same event calls
			if (m_Event.GetType() == type)
			{
				m_Event.m_Handled = func();
				return true;
			}
		}

		// If docking is enabled ImGui is the event handler.
		// ImGui is take control of event because otherwise for example
		// when clicking an ImGui button also touching the background behind itself.
		// This will do something else in the program.
		// This block will be execute if so.

		return false;
	}
}
