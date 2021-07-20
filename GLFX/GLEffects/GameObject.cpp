#include "GameObject.h"

namespace glfx
{
    auto GameObject::BeginPlay() -> void
    {
    }

    auto GameObject::Tick(const double delta_time) -> void
    {
    }

    auto GameObject::GetName() const -> std::string_view
    {
        return "GameObject";
    }
}