#pragma once

namespace glfx::gui
{
	class IGUI
	{
	public:
		virtual ~IGUI() {};
		virtual auto Initialize() -> void = 0;
		virtual auto Render(const double delta_time) -> void = 0;
		//virtual auto Dispose() -> void = 0;
	};
}