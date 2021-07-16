#pragma once

#include <memory>
#include <vector>


namespace glfx
{
	class IRenderable;

	class World
	{
	public:
		void Render();
		void Update(const double delta_time);
		void Add(std::shared_ptr<IRenderable> object);
	private:
		std::vector<std::shared_ptr<IRenderable>> m_objects;
	};
}

