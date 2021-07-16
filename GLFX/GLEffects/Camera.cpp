#include "Camera.h"
#include <GLFW/glfw3.h>

#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>


namespace glfx
{
	auto Camera::GetWorldPosition() const -> glm::dvec3
	{
		return m_camera_props.m_world_position;
	}

	bool first_mouse = true;
	double last_x = {}, last_y = {};
	auto Camera::RotateByMouse(GLFWwindow* window) -> void
	{
		double x_pos = {}, y_pos = {};
		glfwGetCursorPos(window, &x_pos, &y_pos);

		if (first_mouse)
		{
			last_x = x_pos;
			last_y = y_pos;
			first_mouse = false;
		}

		auto xoffset = x_pos - last_x;
		auto yoffset = y_pos - last_y;

		last_x = x_pos;
		last_y = y_pos;

		auto sensitivity = 0.1;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		m_camera_props.m_yaw += xoffset;
		m_camera_props.m_pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped.
		constexpr auto max_pitch = 89.9;
		if (m_camera_props.m_pitch >= max_pitch)	m_camera_props.m_pitch = max_pitch;
		if (m_camera_props.m_pitch <= -max_pitch)	m_camera_props.m_pitch = -max_pitch;
	}

	auto Camera::Animate(GLFWwindow* window, const double delta_time) -> void
	{
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			Translate(CameraDirection::FRONT, delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			Translate(CameraDirection::BACK, delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_A))
		{
			Translate(CameraDirection::LEFT, delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_D))
		{
			Translate(CameraDirection::RIGHT, delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_E))
		{
			Translate(CameraDirection::UP, delta_time);
		}
		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			Translate(CameraDirection::DOWN, delta_time);
		}
	}

	auto CalculateDirectionVectors(const CameraProps& camera_props) -> std::tuple<glm::dvec3, glm::dvec3, glm::dvec3>
	{
		glm::dvec3 direction = {};
		direction.x = cos(glm::radians(camera_props.m_yaw)) * cos(glm::radians(camera_props.m_pitch));
		direction.y = -sin(glm::radians(camera_props.m_pitch));
		direction.z = sin(glm::radians(camera_props.m_yaw)) * cos(glm::radians(camera_props.m_pitch));
		const auto front = glm::normalize(direction);

		constexpr glm::dvec3 world_up = { 0.0, 1.0, 0.0 };

		const auto right = glm::normalize(glm::cross(front, world_up));
		const auto up = glm::normalize(glm::cross(right, front));

		return { front, right, up };
	}

	auto Camera::Translate(const CameraDirection direction_type, const double delta_time) -> void
	{
		const auto [front, right, up] = CalculateDirectionVectors(m_camera_props);
		switch (direction_type) 
		{
			case (CameraDirection::FRONT)	:	m_camera_props.m_world_position += front * 15.0 * delta_time; break;
			case (CameraDirection::BACK)	:	m_camera_props.m_world_position -= front * 15.0 * delta_time; break;
			case (CameraDirection::LEFT)	:	m_camera_props.m_world_position -= right * 15.0 * delta_time; break;
			case (CameraDirection::RIGHT)	:	m_camera_props.m_world_position += right * 15.0 * delta_time; break;
			case (CameraDirection::UP)		:	m_camera_props.m_world_position += up	 * 15.0 * delta_time; break;
			case (CameraDirection::DOWN)	:	m_camera_props.m_world_position -= up	 * 15.0 * delta_time; break;
			default:break;
		}
	}

	auto GetViewMatrix(const CameraProps& camera_props) -> glm::mat4
	{
		const auto [front, right, up] = CalculateDirectionVectors(camera_props);
		return glm::lookAt(camera_props.m_world_position, camera_props.m_world_position + front, up);;
	}

	auto ComputeCameraProjection(const double fov, const double width, const double height, const double z_near, const double z_far) -> glm::mat4
	{
		return glm::perspective(glm::radians(fov), width / height, z_near, z_far);
	}
}