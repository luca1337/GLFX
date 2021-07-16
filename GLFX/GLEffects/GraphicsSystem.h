#pragma once

#include "ISystem.h"

#include <string_view>

namespace glfx
{
	class Window;
	class World;

	class GraphicsSystem final : public ISystem
	{
	public:
		GraphicsSystem();
		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;

		auto Tick(std::shared_ptr<World> world, const double delta_time) -> void override;
	private:
		
	};
}

