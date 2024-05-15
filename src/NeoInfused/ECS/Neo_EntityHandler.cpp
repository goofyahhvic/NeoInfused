#include "Neo_PCH.hpp"
#include "./Neo_EntityHandler.hpp"

namespace neo {
    std::vector<Entity> EntityHandler::entity_registry, EntityHandler::destroyed_entities;

    void EntityHandler::Init() {
        entity_registry.clear();
        destroyed_entities.clear();
    }

    Entity EntityHandler::CreateEntity(void) {
        Entity e;
        if (destroyed_entities.empty()) {
            e.id = entity_registry.size();
            entity_registry.push_back(e);
            return e;
        }
        e.id = destroyed_entities[destroyed_entities.size()-1].id;
        destroyed_entities.pop_back();
        return e;        
    }
    void EntityHandler::DestroyEntity(Entity e) {
        destroyed_entities.push_back(e);
        e.id = UINT64_MAX;
    }

} // namespace neo
