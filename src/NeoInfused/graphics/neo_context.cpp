#include "neo_pch.hpp"
#include "NeoInfused/graphics/neo_context.hpp"

namespace neo {
    Context* Context::m_This = nullptr;
    uint8_t Context::m_API = UINT8_MAX;
    bool Context::m_Initialized = NEO_RENDERERAPI_NONE;
}