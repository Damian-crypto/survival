#pragma once

#include <functional>

namespace zeus
{
	enum class EventType
	{
		None,

		MousePressed,
		MouseReleased,
		MouseMoved,
		MouseScrolled,

		KeyPressed,
		KeyReleased,

		WindowResized
	};

	class Event
	{
	protected:
		EventType m_Type = EventType::None;

	public:
		bool m_Handled = false;

	public:
		Event();
		Event(EventType& type);
		
		EventType GetType();
	};

	class EventDispatcher
	{
	private:
		Event m_Event;

	public:
		EventDispatcher(Event& evt);

		bool Dispatch(EventType type, std::function<bool()>& func);
	};
}
