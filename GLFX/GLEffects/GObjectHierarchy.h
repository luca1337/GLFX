#pragma once

#include "IGUI.h"

namespace glfx::gui
{
	class GObjectHierarchy : public IGUI
	{
	public:
		~GObjectHierarchy() = default;
		GObjectHierarchy() = default;
		GObjectHierarchy(const GObjectHierarchy&) = delete;
		GObjectHierarchy& operator=(const GObjectHierarchy&) = delete;

		virtual auto Initialize() -> void override;
		virtual auto Render(const double delta_time) -> void override;
	};
}