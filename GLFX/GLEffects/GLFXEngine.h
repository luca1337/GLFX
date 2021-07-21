#pragma once

#include "Camera.h"
#include "GUIManager.h"
#include "Shader.h"

#include <memory>
#include <vector>
#include <string_view>

namespace glfx
{
	struct ISystem;
	class Window;
	class World;

	class GLFXEngine final
	{
	public:
		GLFXEngine(const GLFXEngine&) = delete;
		GLFXEngine& operator=(const GLFXEngine&) = delete;
		static auto Get() -> GLFXEngine&;
		auto Initialize(const std::uint32_t width, const std::uint32_t height, const std::string_view title) -> void;
		auto Run() -> void;
		auto ComputeDeltaTime() -> double;
		auto GetMainCamera() -> Camera&;
		auto GetWorld() -> std::shared_ptr<World>;
		auto GetWindow() const -> std::shared_ptr<Window>;
		glfx::Shader solid_shader = {};
		glfx::Shader outline_shader = {};
	private:
		GLFXEngine() = default;
		auto SortSystems() -> void;
		auto AddSystem(std::unique_ptr<ISystem> system) -> void;
	private:
		std::vector<std::unique_ptr<ISystem>> m_systems;

		double m_delta_time = {};
		double m_last_frame = {};

		std::shared_ptr<World> m_world;
		std::shared_ptr<Window> m_window;
		std::shared_ptr<gui::GUIManager> m_gui;
		Camera m_main_camera;

		static uint32_t m_component_counter;

		friend class GameObject;
	};
}

