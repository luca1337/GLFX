#include "Mesh.h"
#include "GameManager.h"
#include "GLFXEngine.h"
#include "Camera.h"
#include "ObjLoader.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glad/glad.h>

namespace glfx
{
	Mesh::Mesh(const std::vector<glm::vec3>& v, const std::vector<glm::vec3>& vn, const std::vector<glm::vec2>& vt)
	{
		GenerateVaoAndVbo(1, &m_vao, 3, m_vbo);

		PushGPUData(v.data(), sizeof(v[0]) * v.size(), 0, 0, 3, sizeof(float) * 3, 0);
		PushGPUData(vn.data(), sizeof(vn[0]) * vn.size(), 1, 1, 3, sizeof(float) * 3, 1);
		PushGPUData(vt.data(), sizeof(vt[0]) * vt.size(), 2, 2, 2, sizeof(float) * 2, 2);

		SetVertices(v);
		SetNormals(vn);
		SetUvs(vt);
	}

	Mesh::Mesh(const std::string& file_name)
	{
		glfx::ObjLoader::Load(file_name, m_vertices, m_uvs, m_normals);

		GenerateVaoAndVbo(1, &m_vao, 3, m_vbo);

		PushGPUData(m_vertices.data(), sizeof(m_vertices[0]) * m_vertices.size(), 0, 0, 3, sizeof(float) * 3, 0);
		PushGPUData(m_normals.data(), sizeof(m_normals[0]) * m_normals.size(), 1, 1, 3, sizeof(float) * 3, 1);
		PushGPUData(m_uvs.data(), sizeof(m_uvs[0]) * m_uvs.size(), 2, 2, 2, sizeof(float) * 2, 2);

		SetVertices(m_vertices);
		SetNormals(m_normals);
		SetUvs(m_uvs);
	}

	auto Mesh::UpdateMatrix(const std::shared_ptr<glfx::Transform>& transform) -> void
	{
		auto& engine = GLFXEngine::Get();

		m_mvp.m_matrix_translation	= glm::translate(glm::mat4(1), transform->m_translation);
		m_mvp.m_matrix_scale		= glm::scale(transform->m_scale);
		m_mvp.m_matrix_rotation		= glm::eulerAngleXYZ(transform->m_rotation.x, transform->m_rotation.y, transform->m_rotation.z);

		const auto model			= m_mvp.m_matrix_translation * m_mvp.m_matrix_scale * m_mvp.m_matrix_rotation;
		const auto view				= glfx::GetViewMatrix(engine.GetMainCamera().m_camera_props);
		const auto projection		= glfx::ComputeCameraProjection(65.0, engine.GetWindow()->GetWidth(), engine.GetWindow()->GetHeight(), 0.01, 1000.0); 
		const auto eye				= GLFXEngine::Get().GetMainCamera().GetWorldPosition();

		m_shader.SetMatrix4x4("model", model);
		m_shader.SetMatrix4x4("view", view);
		m_shader.SetMatrix4x4("projection", projection);
		m_shader.SetVec3("eye", eye);
	}

	auto Mesh::Draw() -> void
	{
		m_shader.Apply();
		//glBindTexture(GL_TEXTURE_2D, texture.GetTexture()); // todo: add texture
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size()));
	}

	auto Mesh::SetShader(const Shader& shader) -> void
	{
		m_shader = shader;
	}

	auto Mesh::GetShader() const -> Shader
	{
		return m_shader;
	}

	auto Mesh::GetVertices() const -> std::vector<glm::vec3>
	{
		return m_vertices;
	}

	auto Mesh::GetVertexNormals() const -> std::vector<glm::vec3>
	{
		return m_normals;
	}

	auto Mesh::GetUvs() const -> std::vector<glm::vec2>
	{
		return m_uvs;
	}

	auto Mesh::SetVertices(const std::vector<glm::vec3>& v_list) -> void
	{
		m_vertices = v_list;
	}

	auto Mesh::SetNormals(const std::vector<glm::vec3>& vt_list) -> void
	{
		m_normals = vt_list;
	}

	auto Mesh::SetUvs(const std::vector<glm::vec2>& vn_list) -> void
	{
		m_uvs = vn_list;
	}

	auto Mesh::PushGPUData(const void* data, const size_t data_size, const size_t vbo_index, const unsigned slot, const int slot_size, const size_t stride, const unsigned attrib_array_index) -> void
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[vbo_index]);
		glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
		glVertexAttribPointer(slot, slot_size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), nullptr);
		glEnableVertexAttribArray(attrib_array_index);
	}

	auto Mesh::GenerateVaoAndVbo(size_t vao_size, unsigned int* vao_array, size_t vbo_size, unsigned int* vbo_array) -> void
	{
		glGenVertexArrays(vao_size, vao_array);
		glBindVertexArray(*vao_array);
		glGenBuffers(vbo_size, vbo_array);
	}
}