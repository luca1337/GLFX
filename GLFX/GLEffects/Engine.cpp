#include "Engine.h"
#include <GLFW/glfw3.h>

namespace glfx
{
	bool glfx::Engine::Init(const int major_version, const int minor_version)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}
}