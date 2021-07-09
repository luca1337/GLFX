#include "World.h"
#include "IRenderable.h"

namespace glfx
{
    void World::Update(const float delta_time)
    {
        for (const auto& object : m_objects)
        {
            object->Render();
            object->Update(delta_time);
        }
    }
}