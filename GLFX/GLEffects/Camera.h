#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace glfx
{
	class Camera
	{
	public:
		Camera(const glm::vec3& world_position);
		void Project(const float fov, const float width, const float height, const float z_near, const float z_far);
		auto GetViewMatrix() const -> glm::mat4;
		auto GetProjectionMatrix() const -> glm::mat4;
		void UpdateMatrix();
	private:
		glm::vec3 m_world_position;

		glm::mat4 m_view;
		glm::mat4 m_projection;
	};
}


