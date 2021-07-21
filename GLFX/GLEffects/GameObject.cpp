#include "GameObject.h"

namespace glfx
{
    GameObject::GameObject(const std::string& name) 
        : m_name(name), m_transform(std::make_shared<glfx::Transform>())
    { }

    auto GameObject::BeginPlay() -> void
    {
    }

    auto GameObject::Tick(const double delta_time) -> void
    {
        for (const auto& component : m_components)
        {
            //todo: check if a component is active or not
            if (!component) continue;

            component->Tick(delta_time);
        }
    }

    auto GameObject::GetName() const -> std::string
    {
        return m_name;
    }
}