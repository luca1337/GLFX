#include "Cube.h"
#include "Utils.h"
#include "MeshRenderer.h"

namespace glfx
{
	Cube::Cube() : GameObject("Cube")
	{
		m_mesh_renderer = std::make_shared<glfx::MeshRenderer>(*this, glfx::MeshFilterType::CUBE);
		AddComponent(m_mesh_renderer);
	}

	auto Cube::Tick(const double delta_time) -> void
	{
		__super::Tick(delta_time);

		std::cout << "ticking GameObject: " << GetName() << std::endl;
	}
}