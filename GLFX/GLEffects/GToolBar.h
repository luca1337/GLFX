#pragma once

#include "IGUI.h"

namespace glfx::gui
{
	class GToolBar : public IGUI
	{
	public:
		~GToolBar() = default;
		GToolBar() = default;
		GToolBar(const GToolBar&) = delete;
		GToolBar& operator=(const GToolBar&) = delete;

		virtual auto Initialize() -> void override;
		virtual auto Render(const double delta_time) -> void override;
	};
}


