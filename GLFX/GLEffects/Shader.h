#pragma once

#include <string_view>

#include <glm/glm.hpp>

namespace glfx
{
	class Shader
	{
	public:
		Shader() = default;
		Shader(const std::string_view vertex, const std::string_view fragment);
		void Apply() const;
		void SetMatrix4x4(const std::string_view name, const glm::mat4& m);
		void SetFloat(const std::string_view name, const float value);
	private:
		unsigned int m_program_id;
	};
}

