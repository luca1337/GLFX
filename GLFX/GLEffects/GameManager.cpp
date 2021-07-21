#include "GameManager.h"
#include "Window.h"
#include "Cube.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

#include "Utils.h"
#include "World.h"
#include "ResourceManager.h"

#include <string_view>
#include <iostream>

namespace glfx
{
	GameManager::GameManager() {}

	GameManager& GameManager::Get()
	{
		static GameManager instance;
		return instance;
	}

	void GameManager::Init(const uint32_t width, const uint32_t height, const std::string_view title)
	{
		auto& engine = GLFXEngine::Get();
		engine.Initialize(width, height, title);
	}

	void GameManager::Run()
	{
		GLFXEngine::Get().Run();
		/*const auto window_handle = m_window->GetWindowHandle();

		glfwSetInputMode(window_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		while (!glfwWindowShouldClose(window_handle))
		{
			const auto delta_time = m_window->ComputeDeltaTime();
			glfwPollEvents();

			glClearColor(0.3, 0.3, 0.8, 1.0);
			glClearStencil(0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			m_camera->RotateByMouse(window_handle);

			// stencil is enabled so it will write into stencil buffer the object

			glStencilFunc(GL_ALWAYS, 1, 0xFF);

			m_cube->SetShader(solid_shader);
			m_cube->SetScale({ 1.0f, 1.0f, 1.0f });
			m_cube->SetPosition({ 6.0f, 0.0f, 0.0f });
			m_cube->Render();
			m_cube->Update(delta_time);

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glDisable(GL_DEPTH_TEST);

			m_cube->SetShader(outline_shader);
			m_cube->SetScale({ 1.02f, 1.02f, 1.02f });
			m_cube->SetPosition({ 6.0f, 0.0f, 0.0f });
			m_cube->Render();
			m_cube->Update(delta_time);

			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);

			glfwSwapBuffers(window_handle);
		}*/
	}
}