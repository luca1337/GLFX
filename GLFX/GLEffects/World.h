#pragma once

#include <memory>
#include <vector>


namespace glfx
{
	class GameObject;

	class World
	{
	public:
		void Update(const double delta_time);
		void Spawn(std::shared_ptr<GameObject> object);
		auto GetGameObjects() const->std::vector<std::shared_ptr<GameObject>>;
		auto ClearWorld() -> void;
	private:
		std::vector<std::shared_ptr<GameObject>> m_objects;
	};
}

