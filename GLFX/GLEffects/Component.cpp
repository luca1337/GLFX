#include "Component.h"

namespace glfx
{
	Component::Component(const std::string& name) :
		m_name(name)
	{
	}

	auto Component::BeginPlay() -> void
	{
	}

	auto Component::Tick(const double delta_time) -> void
	{
	}

	auto Component::GetName() const -> std::string
	{
		return m_name;
	}
}