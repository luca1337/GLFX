#include "World.h"
#include "GameObject.h"

namespace glfx
{
    void World::Update(const double delta_time)
    {
        for (const auto& object : m_objects)
        {
            // todo: check if gameObject is not corrupted and is active

            object->Tick(delta_time);
        }
    }

    void World::Spawn(std::shared_ptr<GameObject> object)
    {
        m_objects.push_back(object);
    }

    auto World::GetGameObjects() const -> std::vector<std::shared_ptr<GameObject>>
    {
        return m_objects;
    }

    auto World::ClearWorld() -> void
    {
        m_objects.clear();
    }
}