#include "corepch.h"
#include "render_command.h"

zeus::RendererInfo zeus::RenderCommand::s_RenderInfo = {};

zeus::RendererInfo zeus::RenderCommand::GetRendererInfo()
{
	return s_RenderInfo;
}
