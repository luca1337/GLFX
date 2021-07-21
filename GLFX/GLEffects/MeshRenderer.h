#pragma once

#include "Component.h"
#include "GLFX.h"
#include "Mesh.h"

namespace glfx
{
	class GameObject;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer(GameObject& m_owner, const MeshFilterType);
		auto Tick(const double delta_time) -> void override;
		static uint32_t m_type;
	private:
		GameObject& m_owner;
		std::shared_ptr<Mesh> m_mesh;
	};
}