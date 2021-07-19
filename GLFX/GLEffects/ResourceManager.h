#pragma once

#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace glfx
{
	template <typename T>
	class Singleton
	{
	public:
		inline static T& GetInstance()
		{
			static T instance = {};
			return instance;
		}
	protected:
		Singleton() {}
		~Singleton() {}
	public:
		Singleton(Singleton const&) = delete;
		Singleton& operator=(Singleton const&) = delete;
	};

	class Resource;

	enum class ResourceType
	{
		SHADERS,
		TEXTURES,
	};

	template <typename T>
	class ResourceManager final : public Singleton<ResourceManager<T>>
	{
		using Resource = std::map<ResourceType, std::map<std::string, T>>;
	public:
		auto Add(const ResourceType, const std::string& resource_name, const T& resource) -> void;
		auto Get(const ResourceType, const std::string& resource_name) -> std::optional<T>;
	private:
		auto Find(const ResourceType, const std::string& resource_name) -> std::optional<T>;
		Resource m_resources;
	};

	template<typename T>
	inline auto ResourceManager<T>::Add(const ResourceType type, const std::string& resource_name, const T& resource) -> void
	{
		if (Find(type, resource_name).has_value())
		{
			std::cout << "resource already exist: " << resource_name << std::endl;
			return;
		}

		m_resources[type][resource_name] = resource;
		std::cout << "resource added: " << resource_name << std::endl;
	}

	template<typename T>
	inline auto ResourceManager<T>::Get(const ResourceType type, const std::string& resource_name) -> std::optional<T>
	{
		T object = {};

		if (const auto& resource = Find(type, resource_name))
		{
			std::cout << "resource found: " << resource_name << std::endl;
			object = resource.value();
		}

		return object;
	}

	template<typename T>
	inline auto ResourceManager<T>::Find(const ResourceType type, const std::string& resource_name) -> std::optional<T>
	{
		const auto first = m_resources.find(type);
		if (first != m_resources.end()) {
			const auto second = m_resources[type].find(resource_name);
			if (second != m_resources[type].end()) {
				return { m_resources[type][resource_name] };
			}
		}
		return {};
	}
}

