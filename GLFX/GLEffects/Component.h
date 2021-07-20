#pragma once

#include <string_view>
#include <cstdint>

namespace glfx
{
	class Component
	{
	public:
		virtual auto BeginPlay() -> void;
		virtual auto Tick(const double delta_time) -> void;
		virtual auto GetName() const -> std::string_view;
		uint32_t m_component_type;
	};
}

