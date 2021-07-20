#include "Component.h"

namespace glfx
{
	auto Component::BeginPlay() -> void
	{
	}

	auto Component::Tick(const double delta_time) -> void
	{
	}

	auto Component::GetName() const -> std::string
	{
		return "";
	}
}