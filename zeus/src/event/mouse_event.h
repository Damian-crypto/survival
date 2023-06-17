#pragma once

#include "event.h"
#include "glm/glm.hpp"

namespace zeus
{
	class MousePressedEvent : public Event
	{
	protected:
		int m_Button;

	public:
		MousePressedEvent(int button);

		uint32_t GetMouseButton();
	};

	class MouseReleasedEvent : public Event
	{
	protected:
		int m_Button;

	public:
		MouseReleasedEvent(int button);

		uint32_t GetMouseButton();
	};

	class MouseMovedEvent : public Event
	{
	protected:
		float m_Xpos;
		float m_Ypos;

	public:
		MouseMovedEvent(float x, float y);

		glm::vec2 GetMousePosition();
	};

	class MouseScrolledEvent : public Event
	{
	protected:
		float m_Xoffset;
		float m_Yoffset;

	public:
		MouseScrolledEvent(float x, float y);

		glm::vec2 GetMouseScroll();
	};
}
