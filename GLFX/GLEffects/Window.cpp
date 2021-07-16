#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

glfx::Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string_view title)
	: m_width(width), m_height(height), m_title(title)
{
	window = glfwCreateWindow(m_width, m_height, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, [](const auto window, const auto width, const auto height) {
		auto& window_ptr = *static_cast<Window*>(glfwGetWindowUserPointer(window));
		window_ptr.m_width = width;
		window_ptr.m_height = height;
		glViewport(0, 0, window_ptr.m_width, window_ptr.m_height);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad" << std::endl;
		return;
	}

	glViewport(0, 0, width, height);
}

auto glfx::Window::GetWindowHandle() const -> GLFWwindow*
{
	return window;
}

auto glfx::Window::GetWidth() const -> uint32_t
{
	return m_width;
}

auto glfx::Window::GetHeight() const -> uint32_t
{
	return m_height;
}