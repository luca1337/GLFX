#pragma once

#include <glad/glad.h>
#include "GameObject.h"

namespace glfx
{
	class Cube : public GameObject
	{
	public:
		Cube();
		auto Tick(const double delta_time) -> void override;
	private:
		std::shared_ptr<class MeshRenderer> m_mesh_renderer;
	};
}