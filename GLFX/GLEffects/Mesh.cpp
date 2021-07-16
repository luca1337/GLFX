#include "Mesh.h"
#include "GameManager.h"
#include "GLFXEngine.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glad/glad.h>

namespace glfx
{
	Mesh::~Mesh()
	{
		glDeleteBuffers(3, m_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Mesh::Update()
	{
		auto& engine = GLFXEngine::Get();

		m_matrix_translation	= glm::translate(glm::mat4(1), m_position);
		m_matrix_scale			= glm::scale(m_scale);
		m_matrix_rotation		= glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z);

		const auto model		= m_matrix_translation * m_matrix_rotation * m_matrix_scale;
		const auto view			= glfx::GetViewMatrix(engine.GetMainCamera().m_camera_props);
		const auto projection	= glfx::ComputeCameraProjection(65.0, engine.GetWindow()->GetWidth(), engine.GetWindow()->GetHeight(), 0.01, 1000.0); 
		const auto eye			= GLFXEngine::Get().GetMainCamera().GetWorldPosition();

		m_shader.SetMatrix4x4("model", model);
		m_shader.SetMatrix4x4("view", view);
		m_shader.SetMatrix4x4("projection", projection);
		m_shader.SetVec3("eye", eye);

	}

	auto Mesh::GetPosition() const -> glm::vec3
	{
		return m_position;
	}

	auto Mesh::GetScale() const -> glm::vec3
	{
		return m_scale;
	}

	auto Mesh::GetRotation() const -> glm::vec3
	{
		return m_rotation;
	}

	auto Mesh::SetPosition(const glm::vec3& v) -> void
	{
		m_position = v;
	}

	auto Mesh::SetScale(const glm::vec3& v) -> void
	{
		m_scale = v;
	}

	auto Mesh::SetRotation(const glm::vec3& v) -> void
	{
		m_rotation = v;
	}

	auto Mesh::SetShader(const Shader& shader) -> void
	{
		m_shader = shader;
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