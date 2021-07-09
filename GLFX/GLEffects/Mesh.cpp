#include "Mesh.h"
#include "GameManager.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace glfx
{
	Mesh::Mesh()
	{
	}

	void Mesh::Update()
	{
		m_matrix_translation	= glm::translate(m_position);
		m_matrix_scale			= glm::scale(m_matrix_translation, m_scale);
		m_matrix_rotation		= glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z);

		const auto model = m_matrix_translation * m_matrix_rotation * m_matrix_scale;
		const auto view = glfx::GameManager::Get().GetCamera()->GetViewMatrix();
		const auto projection = glfx::GameManager::Get().GetCamera()->GetProjectionMatrix();

		m_shader.SetMatrix4x4("model", model);
		m_shader.SetMatrix4x4("view", view);
		m_shader.SetMatrix4x4("projection", projection);
	}
}