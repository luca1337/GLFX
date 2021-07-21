#include "MeshRenderer.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace glfx
{
	uint32_t MeshRenderer::m_type = 0;

	MeshRenderer::MeshRenderer(GameObject& owner, const MeshFilterType mesh_filter_type) : Component("MeshRenderer"), m_owner(owner)
	{
		// todo: change this must be in a file, we can get rid of this constructor, in the other hand we could only
		// use the second constructor when we load meshes from file also it's lightweight

		std::vector<glm::vec3> v =
		{
			// first facet front
			{-1, 1, -1},
			{-1, -1, -1},
			{1, -1, -1},
			{-1, 1, -1},
			{1, 1, -1},
			{1, -1, -1},

			// second facet back
			{-1, 1, 1},
			{-1, -1, 1},
			{1, -1, 1},
			{-1, 1, 1},
			{1, 1, 1},
			{1, -1, 1},

			// third facet left
			{-1, 1, 1},
			{-1, -1, 1},
			{-1, -1, -1},
			{-1, 1, 1},
			{-1, 1, -1},
			{-1, -1, -1},

			// fourth facet right
			{1, 1, 1},
			{1, -1, 1},
			{1, -1, -1},
			{1, 1, 1},
			{1, 1, -1},
			{1, -1, -1},

			// fifth facet up
			{-1, 1, 1},
			{-1, 1, -1},
			{1, 1, -1},
			{-1, 1, 1},
			{1, 1, 1},
			{1, 1, -1},

			// sixth facet down
			{-1, -1, 1},
			{-1, -1, -1},
			{1, -1, -1},
			{-1, -1, 1},
			{1, -1, 1},
			{1, -1, -1}
		};

		std::vector<glm::vec2> vt =
		{
			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},

			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},

			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},

			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},

			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},

			{0, 1},
			{0, 0},
			{1, 0},
			{0, 1},
			{1, 1},
			{1, 0},
		};

		std::vector<glm::vec3> vn =
		{
			{0, 0, -1},
			{0, 0, -1},
			{0, 0, -1},
			{0, 0, -1},
			{0, 0, -1},
			{0, 0, -1},

			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},

			{-1, 0, 0},
			{-1, 0, 0},
			{-1, 0, 0},
			{-1, 0, 0},
			{-1, 0, 0},
			{-1, 0, 0},

			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},

			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},
			{0, 1, 0},

			{0, -1, 0},
			{0, -1, 0},
			{0, -1, 0},
			{0, -1, 0},
			{0, -1, 0},
			{0, -1, 0},
		};

		m_mesh = std::make_shared<glfx::Mesh>(v, vn, vt);
		m_mesh->SetShader(glfx::ResourceManager<glfx::Shader>().GetInstance().Get(glfx::ResourceType::SHADERS, "SolidShader").value());
	}

	auto MeshRenderer::Tick(const double delta_time) -> void
	{
		m_mesh->Draw();
		m_mesh->UpdateMatrix(m_owner.m_transform);
	}
}