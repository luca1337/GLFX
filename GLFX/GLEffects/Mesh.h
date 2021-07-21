#pragma once

#include "Color.h"
#include "Shader.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

namespace glfx
{
	/// <summary>
	/// Base class for all Meshes like [Cube, Sphere, Box, CustomMesh]..
	/// </summary>
	class Mesh
	{
	public:
		Mesh(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& vn, const std::vector<glm::vec2>& vt);
		Mesh(const std::string& file_name);
		auto UpdateMatrix(const std::shared_ptr<glfx::Transform>&) -> void;
		auto Draw() -> void;
		auto SetShader(const Shader&) -> void;
		auto GetShader() const -> Shader;

		auto GetVertices() const -> std::vector<glm::vec3>;
		auto GetVertexNormals() const -> std::vector<glm::vec3>;
		auto GetUvs() const -> std::vector<glm::vec2>;

		auto SetVertices(const std::vector<glm::vec3>& v_list) -> void;
		auto SetNormals(const std::vector<glm::vec3>& vt_list) -> void;
		auto SetUvs(const std::vector<glm::vec2>& vn_list) -> void;
	protected:
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
		struct Mvp {
			glm::mat4 m_matrix_translation	= glm::identity<glm::mat4>();
			glm::mat4 m_matrix_scale		= glm::identity<glm::mat4>();
			glm::mat4 m_matrix_rotation		= glm::identity<glm::mat4>();
		}m_mvp;
	};
}