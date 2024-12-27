#if !defined(NEO_ARRAY_VECTOR_HPP)
#define NEO_ARRAY_VECTOR_HPP

#include "NeoInfused/core/neo_utils.hpp"
#include "./neo_array-iterator.hpp"

namespace neo {
	namespace array_vec {
		enum copy_t { copy };
		enum move_t { move };
		enum set_t { set };
		enum create_elements_t { create_elements };

		template<typename T>
		class array_vec_t {
		public:
			using iterator_t = array::iterator_t<array_vec_t>;
			using reverse_iterator_t = array::reverse_iterator_t<array_vec_t>;
			using const_iterator_t = array::const_iterator_t<array_vec_t>;
			using const_reverse_iterator_t = array::const_reverse_iterator_t<array_vec_t>;
			using T_t = T;
		public:
			inline array_vec_t(void)
			: m_Size(0), m_Buffer(nullptr)
			{}

			inline array_vec_t(size_t size)
			: m_Size(0), m_Buffer(tmalloc<T>(size))
			{
				for (; m_Size < size; m_Size++)
					new (m_Buffer + m_Size) T();
			}

			inline array_vec_t(const T* buffer, size_t size)
			: m_Size(0), m_Buffer(tmalloc<T>(size))
			{
				for (; m_Size < size; m_Size++)
					new (m_Buffer + m_Size) T(buffer[m_Size]);
			}

			inline array_vec_t(move_t, T* buffer, size_t size)
			: m_Size(0), m_Buffer(tmalloc<T>(size))
			{
				for (; m_Size < size; m_Size++)
					new (m_Buffer + m_Size) T(std::move(buffer[m_Size]));
			}

			// dangerous
			inline array_vec_t(set_t, T* buffer, size_t size)
			: m_Size(size), m_Buffer(buffer)
			{}

			inline array_vec_t(const std::initializer_list<T>& list)
			: array_vec_t(list.begin(), list.size())
			{}

			inline ~array_vec_t(void) { this->clear(); free(m_Buffer); }

			inline array_vec_t(const array_vec_t& other)
			: array_vec_t(other.m_Buffer, other.m_Size) {}

			array_vec_t& operator=(const array_vec_t& other)
			{
				if (m_Size != other.m_Size)
				{
					for (size_t i = 0; i < m_Size; i++)
						m_Buffer[i].~T();
					free(m_Buffer);
					m_Buffer = tmalloc<T>(other.m_Size);
				} else
				{
					for (size_t i = 0; i < m_Size; i++)
						m_Buffer[i].~T();
				}

				for (m_Size = 0; m_Size < other.m_Size; m_Size++)
					new (m_Buffer + m_Size) T(other.m_Buffer[m_Size]);

				return *this;
			}

			array_vec_t(array_vec_t&& other)
			{
				memcpy(this, &other, sizeof(array_vec_t));
				memset(&other, 0, sizeof(array_vec_t));
			}

			array_vec_t& operator=(array_vec_t&& other)
			{
				for (size_t i = 0; i < m_Size; i++)
					m_Buffer[i].~T();
				free(m_Buffer);
				memcpy(this, &other, sizeof(array_list_t));
				memset(&other, 0, sizeof(array_list_t));
				return *this;
			}

			inline void clear(void)
			{ 
				for (size_t i = 0; i < m_Size; i++)
					m_Buffer[i].~T();
				free(m_Buffer);
				m_Buffer = nullptr;
				m_Size = 0;
			}

			inline void resize(size_t new_size)
			{
				if (m_Size == new_size)
					return;

				if (m_Size < new_size)
				{
					m_Buffer = trealloc<T>(m_Buffer, new_size);
					for (; m_Size < new_size; m_Size++)
						new (m_Buffer + m_Size) T();
					return;
				}

				for (size_t i = m_Size; i < new_size; i++)
					m_Buffer[i].~T();
				m_Buffer = trealloc<T>(m_Buffer, new_size);
			}

			template<typename... ArgsT>
			size_t emplace(ArgsT&&... __args)
			{
				m_Buffer = trealloc<T>(m_Buffer, ++m_Size);
				new (m_Buffer + m_Size - 1) T(std::forward<ArgsT>(__args)...);
				return m_Size;
			}

			bool pop(void)
			{
				if (m_Size)
				{
					m_Buffer[--m_Size].~T();
					m_Buffer = trealloc<T>(m_Buffer, m_Size);
					return true;
				}
				return false;
			}

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

			[[nodiscard]] inline size_t size(void) const { return m_Size; }
			[[nodiscard]] inline bool empty(void) const { return !m_Size; }
		private:
			size_t m_Size;
			T* m_Buffer;
		};
	} // namespace array_vec
	template<typename T>
	using array_vec_t = array_vec::array_vec_t<T>;

	using bytes_t = neo::array_vec_t<byte_t>;
	using ubytes_t = neo::array_vec_t<ubyte_t>;
} // namespace neo

#endif // NEO_ARRAY_VECTOR_HPP