#if !defined(NEO_WINDOW_STORAGE_HPP)
#define NEO_WINDOW_STORAGE_HPP

#include "../core/neo_window.hpp"

namespace neo {
	class WindowStorage_iterator {
		using _ThisT = WindowStorage_iterator;
	public:
		WindowStorage_iterator(const _ThisT& other) = default;
		WindowStorage_iterator(_ThisT&& other) = default;

		inline _ThisT& operator++(void) { do m_Ptr++; while (!*m_Ptr); return *this; }
		inline _ThisT  operator++(int) { _ThisT temp(m_Ptr); do m_Ptr++; while (!*m_Ptr); return temp; }

		inline _ThisT& operator--(void) { do m_Ptr--; while (!*m_Ptr); return *this; }
		inline _ThisT  operator--(int) { _ThisT temp(m_Ptr); do m_Ptr--; while (!*m_Ptr); return temp; }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline Window** operator->() const { return m_Ptr; }
		[[nodiscard]] inline Window* operator*() const { return *m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const = default;

		WindowStorage_iterator(Window** const ptr)
		: m_Ptr(ptr) { while (!*m_Ptr) m_Ptr++; }
	private:
		Window** m_Ptr;
	};

	class WindowStorage_const_iterator {
		using _ThisT = WindowStorage_const_iterator;
	public:
		WindowStorage_const_iterator(const _ThisT& other) = default;
		WindowStorage_const_iterator(_ThisT&& other) = default;

		inline _ThisT& operator++(void) { do m_Ptr++; while (!*m_Ptr); return *this; }
		inline _ThisT  operator++(int) { _ThisT temp(m_Ptr); do m_Ptr++; while (!*m_Ptr); return temp; }

		inline _ThisT& operator--(void) { do m_Ptr--; while (!*m_Ptr); return *this; }
		inline _ThisT  operator--(int) { _ThisT temp(m_Ptr); do m_Ptr--; while (!*m_Ptr); return temp; }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline const Window** operator->() const { return m_Ptr; }
		[[nodiscard]] inline const Window* operator*() const { return *m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const = default;

		inline WindowStorage_const_iterator(const Window** const ptr)
		: m_Ptr(ptr) { while (!*m_Ptr) m_Ptr++; }
	private:
		const Window** m_Ptr;
	};

	class WindowStorage {
	public:
		using iterator = WindowStorage_iterator;
		using const_iterator = WindowStorage_const_iterator;
	public:
		WindowStorage(void);
		~WindowStorage(void);

		uint32_t create_window(uint32_t width, uint32_t height, const char* title);
		void destroy_window(uint32_t id);

		// destroys all windows and clear the container
		void clear(void);

		// returns the number of living windows in the container
		[[nodiscard]] inline size_t size(void) const { return m_WindowsNum; }

		// returns false if theres more than one living window in the container
		[[nodiscard]] inline bool empty(void) const { return !m_WindowsNum; }

		[[nodiscard]] Window* at(uint32_t id);
		[[nodiscard]] inline Window* operator[](uint32_t id) { return this->at(id); }
		[[nodiscard]] Window* main_window(void) { return this->at(main_window_id); }

		[[nodiscard]] inline iterator begin(void) { return m_Windows; }
		[[nodiscard]] inline const_iterator begin(void) const { return (const Window** const)m_Windows; }
		[[nodiscard]] inline const_iterator cbegin(void) const { return (const Window** const)m_Windows; }

		[[nodiscard]] inline iterator end(void) { return m_Windows + m_Size; }
		[[nodiscard]] inline iterator end(void) const { return m_Windows + m_Size; }
		[[nodiscard]] inline iterator cend(void) const { return m_Windows + m_Size; }
	public:
		uint32_t main_window_id;
	private:
		uint32_t m_WindowsNum, m_Size, m_Capacity;
		Window** m_Windows;
	};
}

#endif // NEO_WINDOW_STORAGE_HPP