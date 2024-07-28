#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window-storage.hpp"

namespace neo {
	WindowStorage_iterator::WindowStorage_iterator(Window** ptr)
	: m_Ptr(ptr) {
		while (!*m_Ptr)
			m_Ptr++;
	}

	WindowStorage::WindowStorage(void)
	: main_window_id(0), m_Size(0), m_WindowsNum(0), m_Capacity(32),
	m_Windows((Window**)malloc(m_Capacity)) {
		NEO_ASSERT(!s_This, "Cannot create multiple instances of WindowStorage!");
		s_This = this;
		m_Windows[0] = (Window*)0xffffffff;
	}
	WindowStorage::~WindowStorage(void) {
		for (uint32_t i = 0; i < m_Size; i++)
			delete m_Windows[i];
	}
	void WindowStorage::clear(void) {
		for (uint32_t i = 0; i < m_Size; i++)
			delete m_Windows[i];
		m_Size = 0;
		m_WindowsNum = 0;
	}

	uint32_t WindowStorage::create_window(uint32_t width, uint32_t height, const std::string& title) {
		if (m_Size == m_Capacity) {
			m_Capacity += 32;
			m_Windows = (Window**)realloc(m_Windows, m_Capacity);
		}
		if (!m_Size) 
			main_window_id = m_Size;
		
		m_Windows[m_Size++] = new Window(m_Size, width, height, title);
		m_Windows[m_Size] = (Window*)INTPTR_MAX;
		m_WindowsNum++;
		return m_Size - 1;
	}
	void WindowStorage::destroy_window(uint32_t id) {
		m_WindowsNum--;
		if (id == m_Size - 1)
			m_Size--;
		delete m_Windows[id];
		m_Windows[id] = nullptr;
	}
	Window* WindowStorage::at(uint32_t id) {
		return m_Windows[id];
	}
}