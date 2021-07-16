#include "UpdateSystem.h"
#include "World.h"

namespace glfx
{
	UpdateSystem::UpdateSystem()
	{
		m_system_type = glfx::ISystemType::UPDATE;
	}

	auto UpdateSystem::Tick(std::shared_ptr<World> world, const double delta_time) -> void
	{
		world->Update(delta_time);
	}
}