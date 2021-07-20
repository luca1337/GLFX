#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace glfx::gui::utils
{
	#define BEGIN_FRAME() {	\
		ImGui_ImplOpenGL3_NewFrame(); \
		ImGui_ImplGlfw_NewFrame(); \
		ImGui::NewFrame(); \
	}

	#define END_FRAME() { \
		ImGui::Render(); \
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());\
	}
}