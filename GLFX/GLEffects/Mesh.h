#pragma once

#include "Color.h"
#include "Vertex.h"
#include "Shader.h"

#include <glm/vec3.hpp>
#include <vector>

namespace glfx
{
	class Mesh
	{
	public:
		Mesh();
		void Update();
	protected:
		glm::vec3 m_position	= { 0, 0, 0 };
		glm::vec3 m_scale		= { 1, 1, 1 };
		glm::vec4 m_rotation	= { 0, 0, 0, 1 };

		glfx::Shader m_shader;

		std::vector<Vertex> m_vertices;
		std::vector<float> m_normals;
		std::vector<float> uvs;
		unsigned int m_vao;
		unsigned int m_vbo[2];
	private:
		glm::mat4 m_matrix_translation;
		glm::mat4 m_matrix_scale;
		glm::mat4 m_matrix_rotation;
	};
}