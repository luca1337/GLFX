#include "Camera.h"
#include <GLFW/glfw3.h>

namespace glfx
{
	Camera::Camera(const glm::vec3& world_position)
		: m_world_position(world_position)
	{
	}

	void Camera::Project(const float fov, const float width, const float height, const float z_near, const float z_far)
	{
		m_projection = glm::perspectiveFovLH(fov, width, height, z_near, z_far);
	}

	auto Camera::GetViewMatrix() const -> glm::mat4
	{
		return m_view;
	}

	auto Camera::GetProjectionMatrix() const -> glm::mat4
	{
		return m_projection;
	}

	void Camera::UpdateMatrix()
	{
		const auto radius = 5.0f;
		const auto cam_x = sin(glfwGetTime()) * radius;
		const auto cam_z = cos(glfwGetTime()) * radius;
		m_view = glm::lookAtLH(glm::vec3(0.0f, 0.0f, radius), glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}