#include "neo_pch.hpp"
#include "NeoInfused/graphics/neo_context.hpp"

namespace neo {
    Context* Context::m_This = nullptr;
    RendererAPI Context::m_API = NEO_RENDERERAPI_NONE;
    bool Context::m_Initialized = false;
}