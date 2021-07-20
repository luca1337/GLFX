#include "GLFXEngine.h"
#include "Camera.h"
#include "Engine.h"
#include "GraphicsSystem.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "UpdateSystem.h"
#include "Window.h"
#include "World.h"

#include <algorithm>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

namespace glfx
{
    auto GLFXEngine::Get() -> GLFXEngine&
    {
        static auto glfx_engine = GLFXEngine{};
        return glfx_engine;
    }

    auto GLFXEngine::Initialize(const std::uint32_t width, const std::uint32_t height, const std::string_view title) -> void
    {
        // init engine global configuration
        Engine::Init(4, 6);

        m_window = std::make_shared<Window>(width, height, title);
        m_world = std::make_shared<World>();
        m_main_camera = {};

        // Shaders
        auto& shader_resource_manager = ResourceManager<Shader>::GetInstance();
        shader_resource_manager.Add(ResourceType::SHADERS, "SolidShader", glfx::Shader("vertex.glsl", "fragment.glsl"));
        shader_resource_manager.Add(ResourceType::SHADERS, "OutlineShader", glfx::Shader("outline_vertex.glsl", "outline_fragment.glsl"));

        // Textures
        auto& textures_resource_manager = ResourceManager<Texture>::GetInstance();
        textures_resource_manager.Add(ResourceType::TEXTURES, "Wall", glfx::Texture("Assets/Textures/wall.jpg"));

        auto graphics_system = std::make_unique<GraphicsSystem>();
        auto update_system = std::make_unique<UpdateSystem>();

        AddSystem(std::move(update_system));
        AddSystem(std::move(graphics_system));

        SortSystems();

        m_gui = std::make_shared<glfx::gui::GUIManager>();
    }

    float x = 0;

    auto GLFXEngine::Run() -> void
    {
        const auto window_handle = m_window->GetWindowHandle();

        //glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // global engine config
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        /*glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/

        m_gui->Init(window_handle);

        while (!glfwWindowShouldClose(window_handle))
        {
            const auto delta_time = ComputeDeltaTime();

            glClearColor(0.2, 0.2, 0.9, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_gui->RenderAll(delta_time);

            // Camera handle
            if (glfwGetMouseButton(window_handle, GLFW_MOUSE_BUTTON_2))
            {
                m_main_camera.RotateByMouse(window_handle);
            }
            else
            {
                m_main_camera.Reset();
            }
            m_main_camera.Animate(window_handle, delta_time);

            for (const auto& system : m_systems)
            {
                system->Tick(m_world, delta_time);
            }

            // imgui
            m_gui->SubmitAll();

            glfwSwapBuffers(window_handle);
            glfwPollEvents();
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window_handle);
        glfwTerminate();
    }

    auto GLFXEngine::SortSystems() -> void
    {
        std::sort(m_systems.begin(), m_systems.end(), [](const auto& a, const auto& b) { return a->m_system_type < b->m_system_type; });
    }

    auto GLFXEngine::AddSystem(std::unique_ptr<ISystem> system) -> void
    {
        m_systems.push_back(std::move(system));
    }

    auto GLFXEngine::ComputeDeltaTime() -> double
    {
        auto current_frame = glfwGetTime();
        m_delta_time = current_frame - m_last_frame;
        m_last_frame = current_frame;
        return m_delta_time;
    }

    auto GLFXEngine::GetMainCamera() -> Camera&
    {
        return m_main_camera;
    }

    auto GLFXEngine::GetWorld() -> std::shared_ptr<World>
    {
        return m_world;
    }

    auto GLFXEngine::GetWindow() const -> std::shared_ptr<Window>
    {
        return m_window;
    }
}