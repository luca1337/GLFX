#pragma once

#include <memory>
#include <iostream>

struct GLFWwindow;

namespace glfx::gui
{
	class GObjectHierarchy;
	class GToolBar;

	class GUIManager
	{
	public:
		auto Init(GLFWwindow*) -> void;
		auto RenderAll(const double delta_time) -> void;
		auto SubmitAll() -> void;
		auto CleanUp() -> void;

	private:
		std::shared_ptr<GObjectHierarchy> m_hierarchy;
		std::shared_ptr<GToolBar> m_tool_bar;
	};
}