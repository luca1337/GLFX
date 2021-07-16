#pragma once

#include "IDisposable.h"

#include <string_view>
#include <glm/glm.hpp>

namespace glfx
{
	class Shader : public IDisposable
	{
	public:
		~Shader();
		Shader() = default;
		Shader(const std::string_view vertex, const std::string_view fragment);
		auto Apply() const -> void;
		auto SetMatrix4x4(const std::string_view name, const glm::mat4& m) -> void;
		auto SetFloat(const std::string_view name, const float value) -> void;
		auto SetVec3(const std::string_view name, const glm::vec3& value) -> void;
		auto Dispose() -> void override;
	private:
		unsigned int m_program_id;
	};
}

