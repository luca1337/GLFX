#include "GameManager.h"
#include "Window.h"
#include "Cube.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

#include <string_view>
#include <iostream>

#include "Utils.h"

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
		// Create window
		m_window = std::make_shared<Window>(width, height, title);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		// Shaders
		solid_shader = glfx::Shader("vertex.glsl", "fragment.glsl");
		outline_shader = glfx::Shader("outline_vertex.glsl", "outline_fragment.glsl");

		// Camera
		m_camera = std::make_shared<Camera>(glm::vec3());
		m_camera->Project(glm::radians(45.0f), (float)m_window->GetWidth(), (float)m_window->GetHeight(), 0.01f, 1000.0f);

		// Spawn objects
		m_cube = std::make_shared<glfx::Cube>();

		solid_shader.Apply();
	}

	void GameManager::Run()
	{
		const auto window_handle = m_window->GetWindowHandle();

		while (!glfwWindowShouldClose(window_handle))
		{
			const auto delta_time = m_window->ComputeDeltaTime();
			glfwPollEvents();

			glClearColor(0, 0, 0, 1.0f);
			glClearStencil(0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			m_camera->UpdateMatrix();

			// Disable stencil testing here in order to draw a normal object

			glStencilFunc(GL_ALWAYS, 1, 0xFF);

			m_cube->SetScale({ 1.0f, 1.0f, 1.0f });
			m_cube->Render(solid_shader);
			m_cube->Update(delta_time);

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glDisable(GL_DEPTH_TEST);

			m_cube->SetScale({ 1.02f, 1.02f, 1.02f });
			m_cube->Render(outline_shader);
			m_cube->Update(delta_time);

			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);

			//std::cout << "delta: " << delta_time << std::endl;

			glfwSwapBuffers(window_handle);
		}
	}

	auto GameManager::GetCamera() const -> std::shared_ptr<Camera>
	{
		return m_camera;
	}
}