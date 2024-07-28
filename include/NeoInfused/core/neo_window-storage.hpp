#if !defined(NEO_WINDOW_STORAGE_HPP)
#define NEO_WINDOW_STORAGE_HPP

#include "neo_window.hpp"

namespace neo {
	class WindowStorage {
	public:
		using iterator = std::vector<Window*>::iterator;
		using reverse_iterator = std::vector<Window*>::reverse_iterator;
		using const_iterator = std::vector<Window*>::const_iterator;
		using const_reverse_iterator = std::vector<Window*>::const_reverse_iterator;
	public:
		WindowStorage(void);
		~WindowStorage(void);
		static inline WindowStorage* Get(void) { return s_This; }

		uint64_t create_window(uint32_t width, uint32_t height, const std::string& title = Core::Get()->exec_name());
		void destroy_window(uint64_t id);

		// destroys all windows and remove clear the container
		void clear(void);
		// returns the number of living windows in the container
		inline size_t size(void) const { return m_Size; }
		// returns false if theres more than one living window in the container
		inline bool empty(void) const { return !m_Size; }

		Window* at(uint64_t id);
		inline Window* operator[](uint64_t id) { return this->at(id); }
		Window* main_window(void) { return this->at(main_window_id); }

		inline iterator begin(void) { return m_Windows.begin(); }
		inline const_iterator begin(void) const { return m_Windows.begin(); }
		inline const_iterator cbegin(void) const { return m_Windows.begin(); }

		inline iterator end(void) { return m_Windows.end(); }
		inline const_iterator end(void) const { return m_Windows.end(); }
		inline const_iterator cend(void) const { return m_Windows.end(); }
		
		inline reverse_iterator rbegin(void) { return m_Windows.rbegin(); }
		inline const_reverse_iterator rbegin(void) const { return m_Windows.rbegin(); }
		inline const_reverse_iterator crbegin(void) const { return m_Windows.rbegin(); }

		inline reverse_iterator rend(void) { return m_Windows.rend(); }
		inline const_reverse_iterator rend(void) const { return m_Windows.rend(); }
		inline const_reverse_iterator crend(void) const { return m_Windows.rend(); }
	public:
		uint64_t main_window_id;
	private:
		std::vector<Window*> m_Windows;
		size_t m_Size;
		static inline WindowStorage* s_This = nullptr;
	};
}

#endif // NEO_WINDOW_STORAGE_HPP