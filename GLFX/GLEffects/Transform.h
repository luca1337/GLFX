#pragma once

#include <glm/common.hpp>

namespace glfx
{
	/// <summary>
	/// A Transform representing a GameObject in the world
	/// </summary>
	struct Transform
	{
		glm::dvec3 m_translation	= {};
		glm::dvec3 m_rotation		= {};

		// todo:
		// note that scale can be replaced with a quaternion
		// so that we ensure no gimbal lock behaviour
		glm::dvec3 m_scale			= { 1, 1, 1 };
	};
}