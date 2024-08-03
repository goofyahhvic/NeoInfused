#if !defined(NEO_EVENT_HANDLER_HPP)
#define NEO_EVENT_HANDLER_HPP

#include "neo_event.hpp"
#include "neo_window.hpp"

namespace neo {
	class EventHandler_iterator {
		using _ThisT = EventHandler_iterator;
	public:
		EventHandler_iterator(const _ThisT& other) = default;
		EventHandler_iterator(_ThisT&& other) = default;

		inline _ThisT& operator++(void) { m_Ptr++; return *this; }
		inline _ThisT  operator++(int) { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int) { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		inline Event* operator->() const { return m_Ptr; }
		inline Event& operator*() const { return *m_Ptr; }

		inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		inline auto operator<=>(const _ThisT& other) const = default;

		EventHandler_iterator(Event* ptr)
		: m_Ptr(ptr) {}
	private:
		Event* m_Ptr;
	};

	class EventHandler_const_iterator {
		using _ThisT = EventHandler_const_iterator;
	public:
		EventHandler_const_iterator(const _ThisT& other) = default;
		EventHandler_const_iterator(_ThisT&& other) = default;

		inline _ThisT& operator++(void) { m_Ptr++; return *this; }
		inline _ThisT  operator++(int) { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int) { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		inline const Event* operator->() const { return m_Ptr; }
		inline const Event& operator*() const { return *m_Ptr; }

		inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		inline auto operator<=>(const _ThisT& other) const = default;

		EventHandler_const_iterator(const Event* ptr)
		: m_Ptr(ptr) {}
	private:
		const Event* m_Ptr;
	};

	class EventHandler {
	public:
		using iterator = EventHandler_iterator;
		using const_iterator = EventHandler_const_iterator;
	public:
		EventHandler(void) : m_Size(0) {}
		~EventHandler(void) = default;

		inline EventHandler& poll_events(void) { m_Size = 0; Window::_GLFWPollEvents(); return *this; }
		inline void push_event(Event&& e) { m_Events[m_Size++] = e; }
		inline void push_event(KeyPressedEvent&& e)          { ((KeyPressedEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(KeyReleasedEvent&& e)         { ((KeyReleasedEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(WindowResizeEvent&& e)        { ((WindowResizeEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(WindowCloseEvent&& e)         { ((WindowCloseEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(WindowFocusEvent&& e)         { ((WindowFocusEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(WindowLostFocusEvent&& e)     { ((WindowLostFocusEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(MouseMovedEvent&& e)          { ((MouseMovedEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(MouseScrolledEvent&& e)       { ((MouseScrolledEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(MouseButtonPressedEvent&& e)  { ((MouseButtonPressedEvent*)m_Events)[m_Size++] = e; }
		inline void push_event(MouseButtonReleasedEvent&& e) { ((MouseButtonReleasedEvent*)m_Events)[m_Size++] = e; }

		[[nodiscard]] inline size_t size(void) const { return m_Size; }
		[[nodiscard]] inline constexpr size_t capacity(void) const { return _CAPACITY; }

		[[nodiscard]] inline iterator begin(void) { return m_Events; }
		[[nodiscard]] inline const_iterator begin(void) const { return m_Events; }
		[[nodiscard]] inline const_iterator cbegin(void) const { return this->begin(); }

		[[nodiscard]] iterator end(void) { return m_Events + m_Size; }
		[[nodiscard]] const_iterator end(void) const { return m_Events + m_Size; }
		[[nodiscard]] const_iterator cend(void) const { return this->end(); }
	private:
		static inline constexpr size_t _CAPACITY = 512;
		Event m_Events[_CAPACITY];
		size_t m_Size;
	};
}

#endif // NEO_EVENT_HANDLER_HPP