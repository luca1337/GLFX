#include "Shader.h"

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace glfx
{
	Shader::~Shader()
	{
		//glDeleteProgram(m_program_id);
	}

	Shader::Shader(const std::string_view vertex, const std::string_view fragment)
	{
		auto ReadShader = [=](const auto path) {
			std::ifstream shader_file = {};
			std::string shader_code = {};
			shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try {
				shader_file.open(path);
				std::stringstream shader_stream = {};
				shader_stream << shader_file.rdbuf();
				shader_file.close();
				shader_code = shader_stream.str();
			}
			catch (const std::ifstream::failure& e) {
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ; " << path << " " << e.what() << std::endl;
			}

			return shader_code;
		};

		// Read shaders
		const auto vertex_shader_code = ReadShader(vertex.data());
		const auto fragment_shader_code = ReadShader(fragment.data());

		const auto to_c_string_vertex_code = vertex_shader_code.c_str();
		const auto to_c_string_fragment_code = fragment_shader_code.c_str();

		// Compile shader
		auto CompileShader = [=](const auto shader_source, const auto shader_type) {
			unsigned int shader = {};
			int success = {};
			char info_log[256] = {};

			shader = glCreateShader(shader_type);
			glShaderSource(shader, 1, &shader_source, nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, info_log);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
			}

			return shader;
		};

		const auto vertex_id = CompileShader(to_c_string_vertex_code, GL_VERTEX_SHADER);
		const auto fragment_id = CompileShader(to_c_string_fragment_code, GL_FRAGMENT_SHADER);

		// Shader program
		m_program_id = glCreateProgram();
		glAttachShader(m_program_id, vertex_id);
		glAttachShader(m_program_id, fragment_id);
		glLinkProgram(m_program_id);

		int success = {};
		char info_log[256] = {};

		glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
		}

		glDeleteShader(vertex_id);
		glDeleteShader(fragment_id);
	}

	auto Shader::Apply() const -> void
	{
		glUseProgram(m_program_id);
	}

	auto Shader::SetMatrix4x4(const std::string_view name, const glm::mat4& m) -> void
	{
		glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.data()), 1, false, &m[0][0]);
	}

	auto Shader::SetFloat(const std::string_view name, const float value) -> void
	{
		glUniform1f(glGetUniformLocation(m_program_id, name.data()), value);
	}

	auto Shader::SetVec3(const std::string_view name, const glm::vec3& value) -> void
	{
		glUniform3fv(glGetUniformLocation(m_program_id, name.data()), 1, &value[0]);
	}

	auto Shader::Dispose() -> void
	{

	}
}