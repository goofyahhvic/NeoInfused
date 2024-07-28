#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window-storage.hpp"

namespace neo {
	WindowStorage::WindowStorage(void)
	: main_window_id(0), m_Size(0) { //, m_IdOffset((uint64_t)rand() + ((uint64_t)rand() << (uint64_t)(rand() % 5)) + (uint64_t)(rand() << 8) + 1) {
		NEO_ASSERT(!s_This, "Cannot create multiple instances of WindowStorage!");
		s_This = this;
	}
	WindowStorage::~WindowStorage(void) {
		for (size_t i = 0; i < m_Windows.size(); i++)
			delete m_Windows[i];
	}
	void WindowStorage::clear(void) {
		for (size_t i = 0; i < m_Windows.size(); i++)
			delete m_Windows[i];
		m_Windows.clear();
		m_Size = 0;
	}

	uint64_t WindowStorage::create_window(uint32_t width, uint32_t height, const std::string& title) {
		if (!m_Size) {
			main_window_id = m_Windows.size();
			m_Windows.push_back(new Window(main_window_id, width, height, title));
		} else {
			m_Windows.push_back(new Window(m_Windows.size(), width, height, title));
		}
		m_Size++;
		return m_Windows.size() - 1;
	}
	void WindowStorage::destroy_window(uint64_t id) {
		m_Size--;
		if (main_window_id == id)
			main_window_id = 0;
		delete m_Windows[id];
		m_Windows[id] = nullptr;
	}
	Window* WindowStorage::at(uint64_t id) {
		return m_Windows[id];
	}
}