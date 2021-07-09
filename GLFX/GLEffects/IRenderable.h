#pragma once

namespace glfx
{
	class IRenderable
	{
	public:
		virtual void Render(Shader& shader) = 0;
		virtual void Update(const double delta_time) = 0;
	};
}