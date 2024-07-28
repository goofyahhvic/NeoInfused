#if !defined(NEO_WINDOW_STORAGE_HPP)
#define NEO_WINDOW_STORAGE_HPP

#include "neo_window.hpp"

namespace neo {
	class WindowStorage_iterator {
		using _ThisT = WindowStorage_iterator;
	public:
		WindowStorage_iterator(const _ThisT& other) = default;
		WindowStorage_iterator(_ThisT&& other) = default;

		inline _ThisT& operator++(void) { do m_Ptr++; while (!*m_Ptr); return *this; }
		inline _ThisT  operator++(int) { _ThisT temp(m_Ptr); do { m_Ptr++; } while (!*m_Ptr); return temp; }

		inline _ThisT& operator--(void) { do { m_Ptr--; } while (!*m_Ptr); return *this; }
		inline _ThisT  operator--(int) { _ThisT temp(m_Ptr); do { m_Ptr--; } while (!*m_Ptr); return temp; }

		inline Window** operator->() const { return m_Ptr; }
		inline Window* operator*() const { return *m_Ptr; }

		inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		inline auto operator<=>(const _ThisT& other) const = default;

		WindowStorage_iterator(Window** ptr);
	private:
		Window** m_Ptr;
	};

	class WindowStorage {
	public:
		using iterator = WindowStorage_iterator;
	public:
		WindowStorage(void);
		~WindowStorage(void);
		static inline WindowStorage* Get(void) { return s_This; }

		uint32_t create_window(uint32_t width, uint32_t height, const std::string& title = Core::Get()->exec_name());
		void destroy_window(uint32_t id);

		// destroys all windows and remove clear the container
		void clear(void);
		// returns the number of living windows in the container
		inline size_t size(void) const { return m_WindowsNum; }
		// returns false if theres more than one living window in the container
		inline bool empty(void) const { return !m_WindowsNum; }

		Window* at(uint32_t id);
		inline Window* operator[](uint32_t id) { return this->at(id); }
		Window* main_window(void) { return this->at(main_window_id); }

		inline iterator begin(void) { return m_Windows; }
		inline iterator end(void) { return m_Windows + m_Size; }
	public:
		uint32_t main_window_id;
	private:
		uint32_t m_WindowsNum, m_Size, m_Capacity;
		Window** m_Windows;
		static inline WindowStorage* s_This = nullptr;
	};
}

#endif // NEO_WINDOW_STORAGE_HPP