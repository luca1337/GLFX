#pragma once

#include "GLFX.h"

namespace glfx
{
	class World;

	struct ISystem
	{
		glfx::ISystemType m_system_type;
		virtual auto Tick(std::shared_ptr<World> world, const double delta_time) -> void = 0;
	};
}