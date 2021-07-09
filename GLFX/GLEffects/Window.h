#pragma once

#include <string_view>

struct GLFWwindow;

namespace glfx
{
	class Window
	{
	public:
		Window(const uint32_t width, const uint32_t height, const std::string_view title);
		auto GetWindowHandle() const -> GLFWwindow*;
		auto GetWidth() const -> uint32_t;
		auto GetHeight() const -> uint32_t;
		auto ComputeDeltaTime() -> double;
	private:
		uint32_t m_width;
		uint32_t m_height;
		std::string_view m_title;

		double m_delta_time = {};
		double m_last_frame = {};

		// gl
		GLFWwindow* window;
	};
}