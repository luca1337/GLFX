#include "GLFXEngine.h"
#include "Camera.h"
#include "Engine.h"
#include "GraphicsSystem.h"
#include "UpdateSystem.h"
#include "Window.h"
#include "World.h"

#include <algorithm>
#include <GLFW/glfw3.h>

#include <iostream>

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
        solid_shader = glfx::Shader("vertex.glsl", "fragment.glsl");
        outline_shader = glfx::Shader("outline_vertex.glsl", "outline_fragment.glsl");

        auto graphics_system = std::make_unique<GraphicsSystem>();
        auto update_system = std::make_unique<UpdateSystem>();

        AddSystem(std::move(update_system));
        AddSystem(std::move(graphics_system));

        SortSystems();
    }

    auto GLFXEngine::Run() -> void
    {
        const auto window_handle = m_window->GetWindowHandle();

        glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // global engine config
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        /*glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);*/

        while (!glfwWindowShouldClose(window_handle))
        {
            const auto delta_time = ComputeDeltaTime();
            glfwPollEvents();

            glClearColor(0.3, 0.3, 0.8, 1.0);
            //glClearStencil(0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Camera handle
            m_main_camera.RotateByMouse(window_handle);
            m_main_camera.Animate(window_handle, delta_time);

            for (const auto& system : m_systems)
            {
                system->Tick(m_world, delta_time);
            }

            glfwSwapBuffers(window_handle);
        }
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