#include "neo_pch.hpp"
#include "NeoInfused/core/neo_scoped-timer.hpp"

namespace neo {
	ScopedTimer::ScopedTimer(const char* name, const ScopedTimer::OnDestroyFn& on_destroy)
		: m_Name(name), m_Time(std::chrono::high_resolution_clock::now()), m_OnDestroy(on_destroy)
	{}
	ScopedTimer::~ScopedTimer(void)
	{
		m_OnDestroy(m_Name, std::chrono::high_resolution_clock::now() - m_Time);
	}
}