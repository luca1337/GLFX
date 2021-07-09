#pragma once

#include <memory>
#include <vector>


namespace glfx
{
	class IRenderable;

	class World
	{
	public:
		void Update(const float delta_time);
	private:
		std::vector<std::shared_ptr<IRenderable>> m_objects;
	};
}

