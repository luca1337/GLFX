#pragma once

#include <functional>

namespace glfx
{
	auto constexpr DEFAULT_WIDTH	= 1920;
	auto constexpr DEFAULT_HEIGHT	= 1080;
	auto constexpr DEFAULT_FOV		= 65.0;

	enum class ISystemType
	{
		GRAPHICS = 0,
		UPDATE = 1,
		PHYSICS = 2,
	};

	enum class MeshFilterType
	{
		CUBE = 0,
		SPHERE = 1,
	};
}