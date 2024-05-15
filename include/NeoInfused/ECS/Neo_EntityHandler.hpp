#if !defined(NEO_ENTITY_HANDLER_HPP)
#define NEO_ENTITY_HANDLER_HPP

#include "./Neo_Entity.hpp"

namespace neo {
    class EntityHandler {
        EntityHandler() = default;
        ~EntityHandler() = default;
    public:
        static void Init(void);

        static Entity CreateEntity(void);
        static void DestroyEntity(Entity e);
    private:
        static std::vector<Entity> entity_registry, destroyed_entities;
    };
} // namespace neo

#endif // NEO_ENTITY_HANDLER_HPP