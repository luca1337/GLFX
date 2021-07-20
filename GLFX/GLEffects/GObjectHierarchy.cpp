#include "GObjectHierarchy.h" 
#include "GLFXEngine.h"
#include "Window.h"
#include "GUIUtils.h"

namespace glfx::gui
{
    const auto WIN_SIZE = ImVec2{ 320, 800 };
    const auto WIN_POS  = ImVec2{ 0, 18 };

    auto GObjectHierarchy::Initialize() -> void
    {
    }

    bool* open = nullptr;
    auto GObjectHierarchy::Render(const double delta_time) -> void
    {
        // start here
        auto& engine = GLFXEngine::Get();

        // set global window flags, for instance: this window cannot be closed as it's "docked" on the left side of the viewport
        auto window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

        // main body of the window, is it's collapsed just early exit for optimization
        if (!ImGui::Begin("Object Hierarchy", open, window_flags))
        {
            ImGui::End();
            return;
        }

        ImGui::SetWindowSize(WIN_SIZE);
        ImGui::SetWindowPos(WIN_POS);

        // start drawing list of objects with all properties

        // end of window..
        ImGui::End();
    }
}