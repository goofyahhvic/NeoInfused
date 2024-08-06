#include "neo_pch.hpp"
#include "NeoInfused/data_structures/neo_window-storage.hpp"

namespace neo {
	WindowStorage::WindowStorage(void)
	: main_window_id(0), m_Size(0), m_WindowsNum(0), m_Capacity(16),
	m_Windows((Window*)malloc(m_Capacity * sizeof(Window))) {

	}
	WindowStorage::~WindowStorage(void) {
		for (uint32_t i = 0; i < m_Size; i++)
			m_Windows[i].destroy();
		free(m_Windows);
	}
	void WindowStorage::clear(void) {
		for (uint32_t i = 0; i < m_Size; i++)
			m_Windows[i].destroy();
		m_Size = 0;
		m_WindowsNum = 0;
	}

	uint32_t WindowStorage::create_window(uint32_t width, uint32_t height, const char* title) {
		if (m_Size == m_Capacity) 
			m_Windows = (Window*)realloc(m_Windows, m_Capacity += 16 * sizeof(Window));
		if (!m_WindowsNum) 
			main_window_id = m_Size;
		
		new (m_Windows + m_Size) Window(m_Size, width, height, title);
		m_Size++;
		m_WindowsNum++;
		return m_Size - 1;
	}
	void WindowStorage::destroy_window(uint32_t id) {
		m_WindowsNum--;
		if (id == m_Size - 1)
			m_Size--;
		m_Windows[id].destroy();
	}
}