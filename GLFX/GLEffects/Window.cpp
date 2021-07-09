#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

glfx::Window::Window(const std::uint32_t width, const std::uint32_t height, const std::string_view title)
	: m_width(width), m_height(height), m_title(title)
{
	window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

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

auto glfx::Window::ComputeDeltaTime() -> double
{
	auto current_frame = glfwGetTime();
	m_delta_time = current_frame - m_last_frame;
	m_last_frame = current_frame;
	return m_delta_time;
}
