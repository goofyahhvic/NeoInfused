#include "neo_pch.hpp"
#include "NeoInfused/data_structures/neo_event-queue.hpp"

namespace neo {
	EventQueue& EventQueue::poll_events(void)
	{
		m_Size = 0;
		glfwPollEvents();
		return *this; 
	}
} // namespace neo

