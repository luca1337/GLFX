#include "GraphicsSystem.h"
#include "World.h"

namespace glfx
{
	GraphicsSystem::GraphicsSystem()
	{
		m_system_type = glfx::ISystemType::GRAPHICS;
	}

	auto GraphicsSystem::Tick(std::shared_ptr<World> world, const double delta_time) -> void
	{
		world->Render();
	}
}