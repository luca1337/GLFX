#pragma once

#include "GLFXEngine.h"
#include "Component.h"
#include "Transform.h"

namespace glfx
{
	/// <summary>
	/// A GameObject is the base class of all object in the world
	/// </summary>
	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		GameObject() = default;
		GameObject(const std::string& name);
		virtual auto BeginPlay() -> void;
		virtual auto Tick(const double delta_time) -> void;
		virtual auto GetName() const -> std::string;
		
		template <typename Type = Component>
		auto AddComponent() -> std::shared_ptr<Type>;

		template <typename Type = Component>
		auto AddComponent(const std::shared_ptr<Type>&) -> std::shared_ptr<Type>;

		template <typename Type = Component>
		auto GetComponent() -> std::optional<std::shared_ptr<Type>>;

	public:
		// transform can be public without any encapsulation
		std::shared_ptr<Transform> m_transform; // can we avoid pointers? and using references instead

	private:
		std::vector<std::shared_ptr<Component>> m_components; // can also be converted to a weak
		std::string m_name;
	};

	template<typename Type>
	inline auto GameObject::AddComponent() -> std::shared_ptr<Type>
	{
		Type::m_type = ++glfx::GLFXEngine::m_component_counter;
		auto new_component = std::make_shared<Type>();
		m_components.push_back(new_component);
		new_component->m_component_type = Type::m_type;
		return new_component;
	}

	template<typename Type>
	inline auto GameObject::AddComponent(const std::shared_ptr<Type>& component) -> std::shared_ptr<Type>
	{
		Type::m_type = ++glfx::GLFXEngine::m_component_counter;
		m_components.push_back(component);
		component->m_component_type = Type::m_type;
		return component;
	}

	template<typename Type>
	inline auto GameObject::GetComponent() -> std::optional<std::shared_ptr<Type>>
	{
		for (const auto& component: m_components)
		{
			if (Type::m_type == component->m_component_type)
			{
				return { std::dynamic_pointer_cast<Type>(component) };
			}
		}

		return { };
	}
}