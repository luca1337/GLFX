#include "World.h"
#include "IRenderable.h"

namespace glfx
{
    void World::Render()
    {
        for (const auto& object : m_objects)
        {
            object->Render();
        }
    }

    void World::Update(const double delta_time)
    {
        for (const auto& object : m_objects)
        {
            object->Update(delta_time);
        }
    }

    void World::Add(std::shared_ptr<IRenderable> object)
    {
        m_objects.push_back(object);
    }
}