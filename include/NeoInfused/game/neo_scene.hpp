#if !defined(NEO_SCENE_HPP)
#define NEO_SCENE_HPP

#include "NeoInfused/core/neo_input.hpp"

namespace neo {
    class Scene {
    public:
        Scene(uint32_t id, Input* input = nullptr);
        virtual ~Scene(void);
    public:
        virtual void on_event(const neo::Event* e) {}
        virtual void update(void) {}
        virtual void draw(void) {}

        virtual void on_set_current(void* data = nullptr) {}
        virtual void on_unset_current(void* data = nullptr) {}
        void set_current(void* set_data = nullptr, void* unset_data = nullptr);

        static inline Scene* GetCurrent(void) { return Scene::m_CurrentScene; }
        static inline Scene* GetFromID(uint32_t id) { return Scene::m_Scenes.at(id); }
        inline uint32_t id(void) const { return m_Id; }

        inline void set_input(Input* new_input) { m_Input = new_input; }
        inline Input* input(void) const { return m_Input; }
    protected:
        uint32_t m_Id;
        Input* m_Input;
    private:
        static Scene* m_CurrentScene;
        static std::unordered_map<uint32_t, Scene*> m_Scenes;
    };
} // namespace neo

#endif // NEO_SCENE_HPP