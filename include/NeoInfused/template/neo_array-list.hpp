#if !defined(NEO_TYPED_ARENA_HPP)
#define NEO_TYPED_ARENA_HPP

#include "../neo_core.hpp"

namespace neo {
	namespace array_list {
		enum copy_t { copy };
		enum move_t { move };
		enum set_t { set };
		enum create_elements_t { create_elements };

		template<typename ArrayListT>
		class iterator_t {
			using T = ArrayListT::T_t;
			using this_t = iterator_t<ArrayListT>;
		public:
			inline this_t& operator++(void) { m_Ptr++; return *this; }
			inline this_t  operator++(int)  { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator--(void) { m_Ptr--; return *this; }
			inline this_t  operator--(int)  { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr += amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr + amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr - amount); }

			[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayListT::reverse_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return m_Ptr <=> other.m_Ptr; }

			iterator_t(T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			T* m_Ptr;
		};

		template<typename ArrayListT>
		class reverse_iterator_t {
			using T = ArrayListT::T_t;
			using this_t = reverse_iterator_t<ArrayListT>;
		public:
			inline this_t& operator++(void) { m_Ptr--; return *this; }
			inline this_t  operator++(int)  { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator--(void) { m_Ptr++; return *this; }
			inline this_t  operator--(int)  { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr += amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr - amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr + amount); }

			[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayListT::iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return other.m_Ptr <=> m_Ptr; }

			reverse_iterator_t(T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			T* m_Ptr;
		};

		template<typename ArrayListT>
		class const_iterator_t {
			using T = ArrayListT::T_t;
			using this_t = const_iterator_t<ArrayListT>;
		public:
			inline this_t& operator++(void) { m_Ptr++; return *this; }
			inline this_t  operator++(int)  { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator--(void) { m_Ptr--; return *this; }
			inline this_t  operator--(int)  { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr += amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr + amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr - amount); }

			[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline const T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline const T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayListT::const_reverse_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other) const  { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return m_Ptr <=> other.m_Ptr; }

			const_iterator_t(const T* const ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			const T* m_Ptr;
		};

		template<typename ArrayListT>
		class const_reverse_iterator_t {
			using T = ArrayListT::T_t;
			using this_t = const_reverse_iterator_t<ArrayListT>;
		public:
			inline this_t& operator++(void) { m_Ptr--; return *this; }
			inline this_t  operator++(int)  { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator--(void) { m_Ptr++; return *this; }
			inline this_t  operator--(int)  { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr += amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr - amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr + amount); }

			[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline const T& operator*(void)  const { return *m_Ptr; }
			[[nodiscard]] inline const T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayListT::const_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return other.m_Ptr <=> m_Ptr; }

			const_reverse_iterator_t(const T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			const T* m_Ptr;
		};

		template<typename T>
		class array_list_t {
		public:
			using iterator_t = iterator_t<array_list_t>;
			using reverse_iterator_t = reverse_iterator_t<array_list_t>;
			using const_iterator_t = const_iterator_t<array_list_t>;
			using const_reverse_iterator_t = const_reverse_iterator_t<array_list_t>;
			using T_t = T;
		public:
			inline array_list_t(size_t capacity = 4, size_t size = 0)
			: m_Capacity(capacity), m_Size(size), m_Buffer(tmalloc<T>(capacity))
			{}

			inline array_list_t(create_elements_t, size_t capacity, size_t size)
			: m_Capacity(capacity), m_Size(0), m_Buffer(tmalloc<T>(capacity))
			{ 
				while (m_Size < size)
					this->emplace_d();
			}

			inline array_list_t(copy_t, const T* buffer, size_t size)
			: m_Capacity(size), m_Size(0), m_Buffer(tmalloc<T>(size))
			{
				while (m_Size < size)
					this->emplace_d(buffer[m_Size]);
			}

			inline array_list_t(move_t, T* buffer, size_t size)
			: m_Capacity(size), m_Size(size), m_Buffer(tmalloc<T>(size))
			{
				while (m_Size < size)
					this->emplace_d(std::move(buffer[m_Size]));
			}

			// dangerous
			inline array_list_t(set_t, T* buffer, size_t size)
			: m_Capacity(size), m_Size(size), m_Buffer(buffer)
			{}

			inline array_list_t(const std::initializer_list<T>& list)
			: array_list_t(copy, list.begin(), list.size())
			{}

			inline ~array_list_t(void) { if (!m_Capacity) return; clear(); free(m_Buffer); }

			inline array_list_t(const array_list_t& other) : array_list_t(copy, other.m_Buffer, other.m_Size) {}
			inline array_list_t& operator=(const array_list_t& other)
			{
				if (m_Capacity < other.m_Capacity)
				{
					free(m_Buffer);
					m_Buffer = tmalloc<T>(other.m_Capacity);
					m_Capacity = other.m_Capacity;
				}
			
				while (m_Size < other.m_Size)
					this->emplace_d(other[m_Size]);

				return *this;
			}

			inline array_list_t(array_list_t&& other)
			{
				memcpy(this, &other, sizeof(array_list_t));
				memset(&other, 0, sizeof(array_list_t));
			}

			inline array_list_t& operator=(array_list_t&& other) {
				free(m_Buffer);
				memcpy(this, &other, sizeof(array_list_t));
				memset(&other, 0, sizeof(array_list_t));
				return *this;
			}

			// capacity is not changed
			inline void clear(void) { while (m_Size) this->pop(); }

			inline void resize(size_t new_size) { m_Size = new_size; }

			inline void resize(create_elements_t, size_t new_size) {
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
				m_Buffer = trealloc<T>(m_Buffer, new_capacity);
				m_Capacity = new_capacity;
			}

			inline void reallocate(size_t new_capacity, size_t new_size)
			{
				m_Size = new_size;
				this->reallocate(new_capacity);
			}

			inline void reallocate(create_elements_t, size_t new_capacity, size_t new_size)
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

			[[nodiscard]] inline iterator_t begin(void) { return m_Buffer; }
			[[nodiscard]] inline const_iterator_t begin(void) const { return m_Buffer; }
			[[nodiscard]] inline const_iterator_t cbegin(void) const { return m_Buffer; }

			[[nodiscard]] inline iterator_t end(void) { return m_Buffer + m_Size; }
			[[nodiscard]] inline const_iterator_t end(void) const { return m_Buffer + m_Size; }
			[[nodiscard]] inline const_iterator_t cend(void) const { return m_Buffer + m_Size; }

			[[nodiscard]] inline reverse_iterator_t rbegin(void) { return m_Buffer + m_Size - 1; }
			[[nodiscard]] inline const_reverse_iterator_t rbegin(void) const { return m_Buffer + m_Size - 1; }
			[[nodiscard]] inline const_reverse_iterator_t crbegin(void) const { return m_Buffer + m_Size - 1; }

			[[nodiscard]] inline reverse_iterator_t rend(void) { return m_Buffer - 1; }
			[[nodiscard]] inline const_reverse_iterator_t rend(void) const { return m_Buffer - 1; }
			[[nodiscard]] inline const_reverse_iterator_t crend(void) const { return m_Buffer - 1; }

			[[nodiscard]] inline iterator_t at(size_t index) { return m_Buffer + index; }
			[[nodiscard]] inline const_iterator_t at(size_t index) const { return m_Buffer + index; }

			[[nodiscard]] inline T& operator[](size_t index) { return m_Buffer[index]; }
			[[nodiscard]] inline const T& operator[](size_t index) const { return m_Buffer[index]; }

			[[nodiscard]] inline T& operator*(void) { return *m_Buffer; }
			[[nodiscard]] inline const T& operator*(void) const { return *m_Buffer; }

			[[nodiscard]] inline T* operator->(void) { return m_Buffer; }
			[[nodiscard]] inline const T* operator->(void) const { return m_Buffer; }

			[[nodiscard]] inline T* ptr(void) { return m_Buffer; }
			[[nodiscard]] inline const T* ptr(void) const { return m_Buffer; }

			[[nodiscard]] inline T& head(void) { return *m_Buffer; }
			[[nodiscard]] inline const T& head(void) const { return *m_Buffer; }

			[[nodiscard]] inline T& tail(void) { return *(m_Buffer + m_Size - 1); }
			[[nodiscard]] inline const T& tail(void) const { return *(m_Buffer + m_Size - 1); }

			[[nodiscard]] inline size_t capacity(void) const { return m_Capacity; }
			[[nodiscard]] inline size_t size(void) const { return m_Size; }
			[[nodiscard]] inline bool empty(void) const { return !m_Size; }
		private:
			size_t m_Capacity, m_Size;
			T* m_Buffer;
		};
	} // namespace array_list
	template<typename T>
	using array_list_t = array_list::array_list_t<T>;
} // namespace neo

#endif // NEO_TYPED_ARENA_HPP