#include "neo_pch.hpp"
#include "NeoInfused/core/neo_event.hpp"

namespace neo {
	event::queue_t& event::poll()
	{
		g_Queue.resize(0);
		glfwPollEvents();
		return g_Queue;
	}
} // namespace neo
