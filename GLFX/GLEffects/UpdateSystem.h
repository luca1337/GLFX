#pragma once

#include "ISystem.h"

namespace glfx
{
	class World;

	class UpdateSystem final : public ISystem
	{
	public:
		UpdateSystem();
		UpdateSystem(const UpdateSystem&) = delete;
		UpdateSystem& operator=(const UpdateSystem&) = delete;

		auto Tick(std::shared_ptr<World> world, const double delta_time) -> void override;
	};
}
