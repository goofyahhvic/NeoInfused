#include "neo_pch.hpp"
#include "NeoInfused/core/neo_event.hpp"

namespace neo {
	event::queue_t& event::poll(event::queue_t& queue)
	{
		queue.resize(0);
		glfwPollEvents();
		return queue;
	}
} // namespace neo
