#pragma once

#include "Window.h"
#include "Shader.h"

#include <memory>

namespace glfx
{
	class Cube;
	class Camera;

	class GameManager final
	{
	public:
		GameManager(const GameManager&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		static GameManager& Get();
		void Init(const uint32_t width, const uint32_t height, const std::string_view title);
		void Run();
		auto GetCamera() const -> std::shared_ptr<Camera>;
	private:
		GameManager();
	private:
		std::shared_ptr<Window> m_window;
		std::shared_ptr<Cube> m_cube;
		std::shared_ptr<Camera> m_camera;
		glfx::Shader solid_shader = {};
		glfx::Shader outline_shader = {};
	};
}

