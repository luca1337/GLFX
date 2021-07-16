#pragma once

namespace glfx
{
	class Shader;

	class IRenderable
	{
	public:
		virtual void Render() = 0;
		virtual void Update(const double delta_time) = 0;
	};
}