#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tuple>
#include <optional>

struct GLFWwindow;

namespace glfx
{
	enum class CameraDirection 
	{
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	struct CameraProps 
	{
		glm::dvec3 m_world_position = { 0.0f, 0.0f, 5.0f };
		glm::mat4 m_projection		= glm::identity<glm::mat4>();
		double m_yaw				= { -90.0 };
		double m_pitch				= { 0.0 };
		double m_fov				= { 65.0 };
	};

	auto GetViewMatrix(const CameraProps&) -> glm::mat4;
	auto ComputeCameraProjection(const double fov, const double width, const double height, const double z_near, const double z_far) -> glm::mat4;

	class Camera
	{
	public:
		auto GetWorldPosition() const -> glm::dvec3;
		auto RotateByMouse(GLFWwindow*) -> void;
		auto Animate(GLFWwindow*, const double delta_time) -> void;
		void Reset() { previous_position.reset(); }
		CameraProps m_camera_props = {};
	private:
		auto Translate(const CameraDirection, const double delta_time) -> void;
		std::optional<glm::dvec2> previous_position;
	};
}


