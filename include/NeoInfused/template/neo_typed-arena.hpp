#if !defined(NEO_TYPED_ARENA_HPP)
#define NEO_TYPED_ARENA_HPP

#include "../neo_core.hpp"

namespace neo {
	template<typename _Arena>
	class Arena_iterator {
		using T = _Arena::T_t;
		using _ThisT = Arena_iterator<_Arena>;
	public:
		inline _ThisT& operator++(void) { m_Ptr++; return *this; }
		inline _ThisT  operator++(int)  { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int)  { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
		[[nodiscard]] inline T* get(void) { return m_Ptr; }
		[[nodiscard]] inline _Arena::reverse_iterator reverse(void) { return m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other)  const { return m_Ptr == other.m_Ptr; }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const { return m_Ptr <=> other.m_Ptr; }

		Arena_iterator(T* ptr = nullptr)
		: m_Ptr(ptr) {}
	private:
		T* m_Ptr;
	};

	template<typename _Arena>
	class Arena_reverse_iterator {
		using T = _Arena::T_t;
		using _ThisT = Arena_reverse_iterator<_Arena>;
	public:
		inline _ThisT& operator++(void) { m_Ptr--; return *this; }
		inline _ThisT  operator++(int)  { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator--(void) { m_Ptr++; return *this; }
		inline _ThisT  operator--(int)  { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr += amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr - amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr + amount); }

		[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
		[[nodiscard]] inline T* get(void) { return m_Ptr; }
		[[nodiscard]] inline _Arena::iterator reverse(void) { return m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other)  const { return m_Ptr == other.m_Ptr; }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const { return other.m_Ptr <=> m_Ptr; }

		Arena_reverse_iterator(T* ptr = nullptr)
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
		inline _ThisT  operator++(int)  { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator--(void) { m_Ptr--; return *this; }
		inline _ThisT  operator--(int)  { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr += amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr + amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr - amount); }

		[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline const T& operator*(void) const { return *m_Ptr; }
		[[nodiscard]] inline const T* get(void) { return m_Ptr; }
		[[nodiscard]] inline _Arena::const_reverse_iterator reverse(void) { return m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other) const  { return m_Ptr == other.m_Ptr; }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const { return m_Ptr <=> other.m_Ptr; }

		Arena_const_iterator(const T* const ptr = nullptr)
		: m_Ptr(ptr) {}
	private:
		const T* m_Ptr;
	};

	template<typename _Arena>
	class Arena_const_reverse_iterator {
		using T = _Arena::T_t;
		using _ThisT = Arena_const_reverse_iterator<_Arena>;
	public:
		inline _ThisT& operator++(void) { m_Ptr--; return *this; }
		inline _ThisT  operator++(int)  { m_Ptr--; return _ThisT(m_Ptr + 1); }

		inline _ThisT& operator--(void) { m_Ptr++; return *this; }
		inline _ThisT  operator--(int)  { m_Ptr++; return _ThisT(m_Ptr - 1); }

		inline _ThisT& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
		inline _ThisT& operator-=(size_t amount) { m_Ptr += amount; return *this; }

		[[nodiscard]] inline _ThisT operator+(size_t amount) const { return _ThisT(m_Ptr - amount); }
		[[nodiscard]] inline _ThisT operator-(size_t amount) const { return _ThisT(m_Ptr + amount); }

		[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
		[[nodiscard]] inline const T& operator*(void)  const { return *m_Ptr; }
		[[nodiscard]] inline const T* get(void) { return m_Ptr; }
		[[nodiscard]] inline _Arena::const_iterator reverse(void) { return m_Ptr; }

		[[nodiscard]] inline bool operator==(const _ThisT& other)  const { return m_Ptr == other.m_Ptr; }
		[[nodiscard]] inline auto operator<=>(const _ThisT& other) const { return other.m_Ptr <=> m_Ptr; }

		Arena_const_reverse_iterator(const T* ptr = nullptr)
		: m_Ptr(ptr) {}
	private:
		const T* m_Ptr;
	};

	template<typename T>
	class Arena {
	public:
		using iterator = Arena_iterator<Arena<T>>;
		using const_iterator = Arena_const_iterator<Arena<T>>;
		using reverse_iterator = Arena_reverse_iterator<Arena<T>>;
		using const_reverse_iterator = Arena_const_reverse_iterator<Arena<T>>;

		using it = iterator;
		using const_it = const_iterator;
		using reverse_it = reverse_iterator;
		using const_reverse_it = const_reverse_iterator;

		using c_it = const_iterator;
		using r_it = reverse_iterator;
		using cr_it = const_reverse_iterator;

		using T_t = T;
	public:
		inline Arena(size_t capacity = 4, size_t size = 0)
		: m_Capacity(capacity), m_Size(size), m_Buffer(malloc_t<T>(capacity))
		{}

		inline Arena(CreateElements, size_t capacity, size_t size)
		: m_Capacity(capacity), m_Size(0), m_Buffer(malloc_t<T>(capacity))
		{ 
			while (m_Size < size)
				this->emplace_d();
		}

		inline Arena(Copy, const T* buffer, size_t size)
		: m_Capacity(size), m_Size(0), m_Buffer(malloc_t<T>(size))
		{
			while (m_Size < size)
				this->emplace_d(buffer[m_Size]);
		}

		inline Arena(Move, T* buffer, size_t size)
		: m_Capacity(size), m_Size(size), m_Buffer(malloc_t<T>(size))
		{
			while (m_Size < size)
				this->emplace_d(std::move(buffer[m_Size]));
		}

		// dangerous
		inline Arena(Set, T* buffer, size_t size)
		: m_Capacity(size), m_Size(size), m_Buffer(buffer)
		{}

		inline Arena(const std::initializer_list<T>& list)
		: Arena(copy, list.begin(), list.size())
		{}

		inline ~Arena(void) { if (!m_Capacity) return; clear(); free(m_Buffer); }

		inline Arena(const Arena& other) : Arena(copy, other.m_Buffer, other.m_Size) {}
		inline Arena& operator=(const Arena& other)
		{
			if (m_Capacity < other.m_Capacity)
			{
				free(m_Buffer);
				m_Buffer = malloc_t<T>(other.m_Capacity);
				m_Capacity = other.m_Capacity;
			}
			
			while (m_Size < other.m_Size)
				this->emplace_d(other[m_Size]);

			return *this;
		}

		inline Arena(Arena&& other)
		{
			memcpy(this, &other, sizeof(Arena));
			memset(&other, 0, sizeof(Arena));
		}

		inline Arena& operator=(Arena&& other) {
			free(m_Buffer);
			memcpy(this, &other, sizeof(Arena));
			memset(&other, 0, sizeof(Arena));
			return *this;
		}

		// capacity is not changed
		inline void clear(void) { while (m_Size) this->pop(); }

		inline void resize(size_t new_size) { m_Size = new_size; }

		inline void resize(CreateElements, size_t new_size) {
			if (new_size > m_Capacity)
				this->reallocate(new_size);
			while (m_Size < new_size)
				this->emplace_d();
			while (m_Size > new_size)
				this->pop();
		}

		inline void reallocate(size_t new_capacity)
		{
			if (new_capacity == m_Capacity)
				return;
			m_Buffer = realloc_t<T>(m_Buffer, new_capacity);
			m_Capacity = new_capacity;
		}

		inline void reallocate(size_t new_capacity, size_t new_size)
		{
			m_Size = new_size;
			this->reallocate(new_capacity);
		}

		inline void reallocate(CreateElements, size_t new_capacity, size_t new_size)
		{
			this->reallocate(new_capacity);
			while (m_Size < new_size)
				this->emplace_d();
		}

		template<typename... _Args>
		inline size_t emplace(_Args&&... __args)
		{
			if (m_Size == m_Capacity)
				this->reallocate(m_Capacity * 2);
			new (m_Buffer + m_Size) T(std::forward<_Args>(__args)...);
			return m_Size++;
		}

		template<typename... _Args>
		inline size_t emplace_d(_Args&&... __args)
		{
			new (m_Buffer + m_Size) T(std::forward<_Args>(__args)...);
			return m_Size++;
		}

		inline void pop(void) { if (m_Size) m_Buffer[--m_Size].~T(); }

		[[nodiscard]] inline iterator begin(void) { return m_Buffer; }
		[[nodiscard]] inline const_iterator begin(void) const { return m_Buffer; }
		[[nodiscard]] inline const_iterator cbegin(void) const { return m_Buffer; }

		[[nodiscard]] inline iterator end(void) { return m_Buffer + m_Size; }
		[[nodiscard]] inline const_iterator end(void) const { return m_Buffer + m_Size; }
		[[nodiscard]] inline const_iterator cend(void) const { return m_Buffer + m_Size; }

		[[nodiscard]] inline reverse_iterator rbegin(void) { return m_Buffer + m_Size - 1; }
		[[nodiscard]] inline const_reverse_iterator rbegin(void) const { return m_Buffer + m_Size - 1; }
		[[nodiscard]] inline const_reverse_iterator crbegin(void) const { return m_Buffer + m_Size - 1; }

		[[nodiscard]] inline reverse_iterator rend(void) { return m_Buffer - 1; }
		[[nodiscard]] inline const_reverse_iterator rend(void) const { return m_Buffer - 1; }
		[[nodiscard]] inline const_reverse_iterator crend(void) const { return m_Buffer - 1; }

		[[nodiscard]] inline iterator at(size_t index) { return m_Buffer + index; }
		[[nodiscard]] inline const_iterator at(size_t index) const { return m_Buffer + index; }

		[[nodiscard]] inline T& operator[](size_t index) { return m_Buffer[index]; }
		[[nodiscard]] inline const T& operator[](size_t index) const { return m_Buffer[index]; }

		[[nodiscard]] inline T& operator*(void) { return *m_Buffer; }
		[[nodiscard]] inline const T& operator*(void) const { return *m_Buffer; }

		[[nodiscard]] inline T* operator->(void) { return m_Buffer; }
		[[nodiscard]] inline const T* operator->(void) const { return m_Buffer; }

		[[nodiscard]] inline T* ptr(void) { return m_Buffer; }
		[[nodiscard]] inline const T* ptr(void) const { return m_Buffer; }

		[[nodiscard]] inline T& first(void) { return *m_Buffer; }
		[[nodiscard]] inline const T& first(void) const { return *m_Buffer; }

		[[nodiscard]] inline T& last(void) { return *(m_Buffer + m_Size - 1); }
		[[nodiscard]] inline const T& last(void) const { return *(m_Buffer + m_Size - 1); }

		[[nodiscard]] inline size_t capacity(void) const { return m_Capacity; }
		[[nodiscard]] inline size_t size(void) const { return m_Size; }
		[[nodiscard]] inline bool empty(void) const { return !m_Size; }
	private:
		size_t m_Capacity, m_Size;
		T* m_Buffer;
	};

	template<typename T>
	using TypedArena = Arena<T>;
}

#endif // NEO_TYPED_ARENA_HPP