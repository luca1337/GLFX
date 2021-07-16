#pragma once

#include <glad/glad.h>
#include "Mesh.h"
#include "IRenderable.h"
#include "ObjLoader.h"
#include "Texture.h"
#include "GLFXEngine.h"

namespace glfx
{
	class Cube : public Mesh, public IRenderable
	{
	public:
		Cube() : Mesh()
		{
			m_vertices =
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

			m_uvs = 
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

			m_normals =
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

			GenerateVaoAndVbo(1, &m_vao, 3, m_vbo);

			texture = Texture("Assets/Textures/wall.jpg");

			// vertices vbo
			PushGPUData(m_vertices.data(), sizeof(m_vertices[0])* m_vertices.size(), 0, 0, 3, sizeof(float) * 3, 0);
			PushGPUData(m_normals.data(), sizeof(m_normals[0]) * m_normals.size(), 1, 1, 3, sizeof(float) * 3, 1);
			PushGPUData(m_uvs.data(), sizeof(m_uvs[0]) * m_uvs.size(), 2, 2, 2, sizeof(float) * 2, 2);
		}

		void Render()
		{
			m_shader.Apply();
			glBindTexture(GL_TEXTURE_2D, texture.GetTexture());
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
		}

		void Update(const double delta_time)
		{
			// apply rotation around Y axis
			m_rotation.y += (float)(glm::radians(45.0f) * delta_time);

			Mesh::Update();
		}

		private:
			Texture texture;
	};
}