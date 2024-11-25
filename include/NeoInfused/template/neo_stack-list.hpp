#if !defined(NEO_SINGLE_LIST_HPP)
#define NEO_SINGLE_LIST_HPP

#include "neo_single-list-iterator.hpp"
#include "neo_list-node.hpp"

namespace neo {
	namespace list {
		template<typename T>
		class stack_t {
		public:
			using node_t = single_node_t<stack_t>;
			using iterator_t = single_iterator_t<stack_t>;
			using const_iterator_t = single_const_iterator_t<stack_t>;
			using T_t = T;
		public:
			inline stack_t(void)
			: m_Head(nullptr), m_Size(0) {}

			inline ~stack_t(void) { this->clear(); }
			inline void clear(void) { while (this->pop_front()); }

			stack_t(copy_t, const T* buffer, size_t size)
			: m_Head(nullptr), m_Size(0)
			{
				size_t i = size;
				while (m_Size < size)
					this->emplace_front(buffer[--i]);
			}

			stack_t(move_t, T* buffer, size_t size)
			: m_Head(nullptr), m_Size(0)
			{
				size_t i = size;
				while (m_Size < size)
					this->emplace_front(std::move(buffer[--i]));
			}

			stack_t(const std::initializer_list<T>& list)
			: stack_t(copy, list.begin(), list.size()) {}

			inline stack_t(stack_t&& other)
			{
				memcpy(this, &other, sizeof(stack_t));
				memset(&other, 0, sizeof(stack_t));
			}

			inline stack_t& operator=(stack_t&& other)
			{
				this->clear();
				memcpy(this, &other, sizeof(stack_t));
				memset(&other, 0, sizeof(stack_t));
				return *this;
			}

			template<typename... ArgsT>
			T* emplace_front(ArgsT&&... __args)
			{
				m_Size++;
				return &((m_Head = new node_t(m_Head, std::forward<ArgsT>(__args)...))->data);
			}

			bool pop_front(void)
			{
				if (!m_Head)
					return false;

				m_Size--;
				node_t* new_head = m_Head->next;
				delete m_Head;
				m_Head = new_head;
				
				return true;
			}

			[[nodiscard]] inline iterator_t begin(void) { return m_Head; }
			[[nodiscard]] inline const_iterator_t begin(void) const { return m_Head; }
			[[nodiscard]] inline const_iterator_t cbegin(void) const { return m_Head; }

			[[nodiscard]] inline iterator_t end(void) { return nullptr; }
			[[nodiscard]] inline const_iterator_t end(void) const { return nullptr; }
			[[nodiscard]] inline const_iterator_t cend(void) const { return nullptr; }

			[[nodiscard]] inline iterator_t at(size_t index) { return iterator_t(m_Head, index); }
			[[nodiscard]] inline const_iterator_t at(size_t index) const { return const_iterator_t(m_Head, index); }

			[[nodiscard]] inline T& operator[](size_t index) { return *(this->at(index)); }
			[[nodiscard]] inline const T& operator[](size_t index) const { return *(this->at(index)); }

			[[nodiscard]] inline T& head(void) { return *m_Head; }
			[[nodiscard]] inline const T& head(void) const { return *m_Head; }
				
			[[nodiscard]] inline size_t size(void) { return m_Size; }
			[[nodiscard]] inline size_t empty(void) { return !m_Size; }
		private:
			node_t* m_Head;
			size_t m_Size;
		};
	} // namespace list

	template<typename T>
	using stack_list_t = list::stack_t<T>;

	template<typename T>
	using stack_list_node_t = list::stack_t<T>::node_t;
} // namespace neo

#endif // NEO_SINGLE_LIST_HPP