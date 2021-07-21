#pragma once

#include <string_view>
#include <cstdint>

namespace glfx
{
	class Component
	{
	public:
		Component(const std::string& name);
		virtual auto BeginPlay() -> void;
		virtual auto Tick(const double delta_time) -> void;
		virtual auto GetName() const -> std::string;
		uint32_t m_component_type;
	private:
		std::string m_name;
	};
}

