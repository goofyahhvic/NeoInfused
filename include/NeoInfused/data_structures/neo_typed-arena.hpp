#if !defined(NEO_TYPED_ARENA_HPP)
#define NEO_TYPED_ARENA_HPP

#include "NeoInfused/neo_core.hpp"
#include "neo_pch.hpp"

namespace neo {
	template<typename _Arena>
	class Arena_iterator {
		using T = _Arena::T_t;
		using _ThisT = Arena_iterator<_Arena>;
	public:
		inline _ThisT& operator++(void) { m_Ptr++; return *this; }
		inline _ThisT  operator++(int)  { m_Ptr++; return _This(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int)  { m_Ptr--; return _This(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline T& operator*(void) const  { return *m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const = default;

		Arena_iterator(T* ptr)
		: m_Ptr(ptr) {}
	private:
		T* m_Ptr;
	};

	template<typename _Arena>
	class Arena_const_iterator {
		using T = _Arena::T_t;
		using _ThisT = Arena_const_iterator<_Arena>;
	public:
		inline _ThisT& operator++(void) { m_Ptr++; return *this; }
		inline _ThisT  operator++(int) { m_Ptr++; return _This(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int) { m_Ptr--; return _This(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline const T& operator*(void) const { return *m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other) const { return (m_Ptr == other.m_Ptr); }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const = default;

		Arena_const_iterator(const T* const ptr)
		: m_Ptr(ptr) {}
	private:
		const T* m_Ptr;
	};

	template<typename T>
	class Arena {
	public:
		using iterator = Arena_iterator<Arena<T>>;
		using const_iterator = Arena_const_iterator<Arena<T>>;
		using T_t = T;
	public:
		inline Arena(uint32_t capacity)
		: m_Capacity(capacity), m_Size(0), m_Buffer((T*)malloc(m_Capacity * sizeof(T)))
		{}
		inline ~Arena(void) { free(m_Buffer); }
		inline void clear(void) { m_Size = 0; }

		template<typename... _Args>
		inline T* push(_Args&&... __args) {
			if (m_Size == m_Capacity)
				m_Buffer = (T*)realloc(m_Buffer, m_Capacity * 2);
			return new (m_Buffer + m_Size++) T(std::forward<_Args>(__args)...);
		}

		[[nodiscard]] inline iterator begin(void) { return m_Buffer; }
		[[nodiscard]] inline const_iterator begin(void) const { return m_Buffer; }
		[[nodiscard]] inline const_iterator cbegin(void) const { return m_Buffer; }

		[[nodiscard]] inline iterator end(void) { return m_Buffer + m_Size; }
		[[nodiscard]] inline const_iterator end(void) const { return m_Buffer + m_Size; }
		[[nodiscard]] inline const_iterator cend(void) const { return m_Buffer + m_Size; }

		[[nodiscard]] inline iterator at(uint32_t index) { return m_Buffer + index; }
		[[nodiscard]] inline const_iterator at(uint32_t index) const { return m_Buffer + index; }

		[[nodiscard]] inline T& operator[](uint32_t index) { return *(m_Buffer + index); }
		[[nodiscard]] inline const T& operator[](uint32_t index) const { return *(m_Buffer + index); }

		[[nodiscard]] inline uint32_t capacity(void) const { return m_Capacity; }
		[[nodiscard]] inline uint32_t size(void) const { return m_Size; }
		[[nodiscard]] inline bool empty(void) const { return !m_Size; }
	private:
		uint32_t m_Capacity, m_Size;
		T* m_Buffer;
	};
}

#endif // NEO_TYPED_ARENA_HPP