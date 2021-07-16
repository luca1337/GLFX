#pragma once

#include "Color.h"
#include "Vertex.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace glfx
{
	class Mesh
	{
	public:
		virtual ~Mesh();
		Mesh() = default;
		void Update();

		auto GetPosition() const -> glm::vec3;
		auto GetScale() const -> glm::vec3;
		auto GetRotation() const -> glm::vec3;

		auto SetPosition(const glm::vec3& v) -> void;
		auto SetScale(const glm::vec3& v) -> void;
		auto SetRotation(const glm::vec3& v) -> void;

		auto SetShader(const Shader& shader) -> void;

	protected:
		glm::vec3 m_position	= { 0, 0, 0 };
		glm::vec3 m_rotation	= { 0, 0, 0 };
		glm::vec3 m_scale		= { 1, 1, 1 };

		glfx::Shader m_shader	= {};

		std::vector<glm::vec3> m_vertices	= {};
		std::vector<glm::vec3> m_normals	= {};
		std::vector<glm::vec2> m_uvs		= {};

		unsigned int m_vao		= {};
		unsigned int m_vbo[3]	= {};

		auto PushGPUData(const void* data,
			const size_t data_size,
			const size_t vbo_index,
			const unsigned slot,
			const int slot_size,
			const size_t stride,
			const unsigned attrib_array_index) -> void;

		auto GenerateVaoAndVbo(size_t vao_size, unsigned int* vao_array, size_t vbo_size, unsigned int* vbo_array) -> void;

	private:
		glm::mat4 m_matrix_translation	= glm::identity<glm::mat4>();
		glm::mat4 m_matrix_scale		= glm::identity<glm::mat4>();
		glm::mat4 m_matrix_rotation		= glm::identity<glm::mat4>();
	};
}