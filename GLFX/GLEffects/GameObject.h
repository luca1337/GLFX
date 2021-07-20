#pragma once

#include "Component.h"
#include "GLFXEngine.h"
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
		virtual auto BeginPlay() -> void;
		virtual auto Tick(const double delta_time) -> void;
		virtual auto GetName() const -> std::string_view;
		
		template <typename Type = Component>
		auto AddComponent() -> std::shared_ptr<Type>;

		template <typename Type = Component>
		auto GetComponent() -> std::optional<std::shared_ptr<Type>>;

	protected:
		std::shared_ptr<Transform> m_transform;

	private:
		std::vector<std::shared_ptr<Component>> m_components; // can also be converted to a weak
	};

	template<typename Type>
	inline auto GameObject::AddComponent() -> std::shared_ptr<Type>
	{
		Type::m_type = ++glfx::GLFXEngine::m_component_counter;
		const auto new_component = std::make_shared<Type>();
		m_components.push_back(new_component);
		new_component->m_component_type = Type::m_type;
		return new_component;
	}

	template<typename Type>
	inline auto GameObject::GetComponent() -> std::optional<std::shared_ptr<Type>>
	{
		auto found_component = std::make_shared<Type>();

		for (const auto& component : m_components)
		{
			if (Type::type != component->m_component_type)
				continue;

			found_component = component;
		}

		return { std::dynamic_pointer_cast<Type>(found_component) };
	}
}