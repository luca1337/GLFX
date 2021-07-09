#pragma once

#include <glad/glad.h>
#include "Mesh.h"
#include "IRenderable.h"
#include "Shader.h"

namespace glfx
{
	class Cube : public Mesh, public IRenderable
	{
	public:
		Cube() : Mesh()
		{
			m_vertices =
			{
				// first face front
				{-1, 1, -1},
				{-1, -1, -1},
				{1, -1, -1},
				{-1, 1, -1},
				{1, 1, -1},
				{1, -1, -1},

				// second face back
				{-1, 1, 1},
				{-1, -1, 1},
				{1, -1, 1},
				{-1, 1, 1},
				{1, 1, 1},
				{1, -1, 1},

				// third face left
				{-1, 1, 1},
				{-1, -1, 1},
				{-1, -1, -1},
				{-1, 1, 1},
				{-1, 1, -1},
				{-1, -1, -1},

				// fourth face right
				{1, 1, 1},
				{1, -1, 1},
				{1, -1, -1},
				{1, 1, 1},
				{1, 1, -1},
				{1, -1, -1},

				// fifth face up
				{-1, 1, 1},
				{1, 1, 1},
				{-1, 1, -1},
				{-1, 1, -1},
				{1, 1, 1},
				{1, 1, -1},

				// sixth facen down
				{-1, -1, -1},
				{-1, -1, 1},
				{1, -1, 1},
				{1, -1, -1},
				{1, -1, 1},
				{-1, -1, -1}
			};

			m_normals =
			{
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,
				0, 0, -1,

				0, 0, 1,
				0, 0, 1,
				0, 0, 1,
				0, 0, 1,
				0, 0, 1,
				0, 0, 1,

				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,
				-1, 0, 0,

				1, 0, 1,
				1, 0, 1,
				1, 0, 1,
				1, 0, 1,
				1, 0, 1,
				1, 0, 1,

				0, 1, 1,
				0, 1, 1,
				0, 1, 1,
				0, 1, 1,
				0, 1, 1,
				0, 1, 1,

				0, -1, 1,
				0, -1, 1,
				0, -1, 1,
				0, -1, 1,
				0, -1, 1,
				0, -1, 1,
			};

			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);

			constexpr auto buffers_num = 2;

			// start creating our vbo's
			glGenBuffers(buffers_num, m_vbo);

			// vertices vbo
			auto PushData = [&](const auto& data,
				const size_t vbo_index,
				const auto slot,
				const auto slot_size,
				const size_t stride,
				const auto attrib_array_index) 
			{
					glBindBuffer(GL_ARRAY_BUFFER, m_vbo[vbo_index]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), data.data(), GL_STATIC_DRAW);
					glVertexAttribPointer(slot, slot_size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), nullptr);
					glEnableVertexAttribArray(attrib_array_index);
			};

			PushData(m_vertices, 0, 0, 3, sizeof(float) * 3, 0);
			PushData(m_normals, 1, 1, 3, sizeof(float) * 3, 1);
		}

		void SetScale(const glm::vec3& v)
		{
			m_scale = v;
		}

		void Render(Shader& shader)
		{
			shader.Apply();
			glBindVertexArray(m_vao);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
		}

		void Update(const double delta_time)
		{
			m_rotation.y += (float)(glm::radians(45.0f) * delta_time);

			Mesh::Update();
		}
	};
}