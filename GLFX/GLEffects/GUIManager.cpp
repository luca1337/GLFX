#include "GUIManager.h"
#include "GObjectHierarchy.h"
#include "GToolBar.h"
#include "GUIUtils.h"

#include <GLFW/glfw3.h>

namespace glfx::gui
{
    auto GUIManager::Init(GLFWwindow* window) -> void
    {
        IMGUI_CHECKVERSION();

        // todo: handle errors properly
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();

        m_hierarchy = std::make_shared<GObjectHierarchy>();
        m_tool_bar = std::make_shared<GToolBar>();
    }

    auto GUIManager::RenderAll(const double delta_time) -> void
    {
        // just call it here 1 time
        BEGIN_FRAME();

        m_tool_bar->Render(delta_time);
        m_hierarchy->Render(delta_time);
    }

    auto GUIManager::SubmitAll() -> void
    {
        END_FRAME();
    }

    auto GUIManager::CleanUp() -> void
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}