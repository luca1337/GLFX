#include "GObjectHierarchy.h" 
#include "GLFXEngine.h"
#include "Window.h"
#include "World.h"
#include "GUIUtils.h"
#include "GameObject.h"
#include "Cube.h"

#include <glm/gtc/type_ptr.hpp>

namespace glfx::gui
{
    const auto HIERARCHY_WIN_SIZE = ImVec2{ 320, 800 };
    const auto HIERARCHY_WIN_POS  = ImVec2{ 0, 18 };

    const auto OBJ_PROPERTIES_WIN_SIZE = ImVec2{ 320, 200 };
    const auto OBJ_PROPERTIES_WIN_POS = ImVec2{ 1920 - 320, 18 };

    auto GObjectHierarchy::Initialize() -> void
    {
    }

    bool* open = nullptr;
    std::shared_ptr<Cube> selected_object = {};
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

        // first window for hierarchy
        ImGui::SetWindowSize(HIERARCHY_WIN_SIZE);
        ImGui::SetWindowPos(HIERARCHY_WIN_POS);

        if (ImGui::Button("Spawn GameObject"))
        {
            auto cube = std::make_shared<Cube>();
            engine.GetWorld()->Spawn(cube);
        }

        if (ImGui::Button("Clear World"))
        {
            engine.GetWorld()->ClearWorld();
            selected_object = {};
        }

        
        for (size_t i = 0; i != engine.GetWorld()->GetGameObjects().size(); i++)
        {
            auto object = engine.GetWorld()->GetGameObjects()[i];

            char buf[256] = {};
            sprintf(buf, "[World] %s", object->GetName().c_str());
            if (ImGui::MenuItem(buf, "GameObject"))
            {
                // can also be created directly as a cube
                selected_object = std::reinterpret_pointer_cast<Cube>(object);
            }
        }

        ImGui::ShowDemoWindow();

        if (ImGui::Begin("[Object Properties]"), open, window_flags)
        {
            // second window for selected object
            ImGui::SetWindowSize(OBJ_PROPERTIES_WIN_SIZE);
            ImGui::SetWindowPos(OBJ_PROPERTIES_WIN_POS);

            if (selected_object)
            {
                if (ImGui::TreeNode("Transform"))
                {
                    ImGui::Spacing();
                    ImGui::Text("Translation");
                    ImGui::AlignTextToFramePadding();
                    const char* labels[] = {"X:", "Y:", "Z:"};

                    constexpr auto number_of_items = 3;
                    for (size_t i = 0; i != number_of_items; i++)
                    {
                        ImGui::PushID("translation##" + *labels[i]);
                        ImGui::Text(labels[i]); ImGui::SameLine();
                        ImGui::SetNextItemWidth(50.0f);
                        ImGui::DragFloat("", &selected_object->m_transform->m_translation[i], 0.01f, -10000.0f, 1000.0f); ImGui::SameLine();
                        ImGui::PopID();
                    }

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Text("Rotation");
                    ImGui::AlignTextToFramePadding();

                    for (size_t i = 0; i != number_of_items; i++)
                    {
                        ImGui::PushID("rotation##" + *labels[i]);
                        ImGui::Text(labels[i]); ImGui::SameLine();
                        ImGui::SetNextItemWidth(50.0f);
                        ImGui::DragFloat("", &selected_object->m_transform->m_rotation[i], 0.01f, -10000.0f, 1000.0f); ImGui::SameLine();
                        ImGui::PopID();
                    }

                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Text("Scale");
                    ImGui::AlignTextToFramePadding();

                    for (size_t i = 0; i != number_of_items; i++)
                    {
                        ImGui::PushID("scale##" + *labels[i]);
                        ImGui::Text(labels[i]); ImGui::SameLine();
                        ImGui::SetNextItemWidth(50.0f);
                        ImGui::DragFloat("", &selected_object->m_transform->m_scale[i], 0.01f, -10000.0f, 1000.0f); ImGui::SameLine();
                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }
            }

            ImGui::End();
        }

        // start drawing list of objects with all properties

        // end of window..
        ImGui::End();
    }
}