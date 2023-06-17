#pragma once

#include "renderer/render_command.h"

#include <cstdint>

namespace zeus
{
	class OpenGLRenderer : public RenderCommand
	{
	private:
		VertexArray m_VertexArray;

		uint32_t m_VAO = 0;	// Vertex Array Object id
		uint32_t m_VBO = 0;	// Vertex Buffer Object id
		uint32_t m_EBO = 0;	// Element Buffer Object id
		uint32_t m_Buffers = 0;	// Buffers to be cleared using bitset

		// m_IndexedRendering should be enabled if you draw by elements
		bool m_IndexedRendering = true;

	public:
		/// <summary>
		/// This constructor may not be execute in the context of OpenGL.
		/// So, don't use OpenGL functions inside this constructor.
		/// </summary>
		OpenGLRenderer() = default;

		/// <summary>
		/// Initializes the opengl rendering part. This should be performed
		/// after the opengl context is created (glfwMakeContextCurrent()).
		/// </summary>
		/// <param name="vertexArray">vertex data to be rendered by this renderer (see what is RenderCommand)</param>
		void Init(const VertexArray& vertexArray) override;
		/// <summary>
		/// Draw call for this renderer. This is a batch rendering system.
		/// All the things will be renderer in a single draw call.
		/// </summary>
		/// <param name="mode">OpenGL has a list of drawing mode (TRIANGLES, LINE_STRIP, etc.)</param>
		void Draw(DrawingMode mode) override;
		/// <summary>
		/// This will set all the flags needed for this renderer.
		/// e.g., GL_DEPTH_TEST, GL_STENCIL, etc.
		/// </summary>
		/// <param name="flag">Set bits for each flag</param>
		void SetState(uint32_t flag) override;
		/// <summary>
		/// This is a deprecated function (as OpenGL says).
		/// This is change the size of the line when rendering in OpenGL.
		/// </summary>
		/// <param name="width">width of the line</param>
		void SetLineWidth(float width) override;
		/// <summary>
		/// This will clear the all the setted buffer. Setting done by SetState(flag) above.
		/// </summary>
		void ClearBuffers() const override;
		/// <summary>
		/// This function can be execute by any renderer (there could be many renderers e.g., QuadRenderer, LineRenderer, etc.).
		/// This function clears the current window with a specified color.
		/// </summary>
		/// <param name="r">red</param>
		/// <param name="g">green</param>
		/// <param name="b">blue</param>
		/// <param name="a">alpha</param>
		void ClearColor(float r, float g, float b, float a) const override;

	private:
		void ReplaceVertexData();
	};
}
