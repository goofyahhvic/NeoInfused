#if !defined(NEO_LINKED_LIST_HPP)
#define NEO_LINKED_LIST_HPP

#include "NeoInfused/core/neo_utils.hpp"
#include "neo_double-list-iterator.hpp"
#include "neo_list-node.hpp"

namespace neo {
	namespace list {
		template<typename T>
		class double_t {
		public:
			using node_t = double_node_t<double_t>;
			using iterator_t = double_iterator_t<double_t>;
			using const_iterator_t = double_const_iterator_t<double_t>;
			using reverse_iterator_t = double_reverse_iterator_t<double_t>;
			using const_reverse_iterator_t = double_const_reverse_iterator_t<double_t>;
			using T_t = T;
		public:
			inline double_t(void) : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}
			inline ~double_t(void) { this->clear(); }
			inline void clear(void) { while (this->pop_back()); }

			double_t(copy_t, const T* buffer, size_t size)
			: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
			{
				while (m_Size < size)
					this->emplace_back(buffer[m_Size]);
			}

			double_t(move_t, T* buffer, size_t size)
			: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
			{
				while (m_Size < size)
					this->emplace_back(std::move(buffer[m_Size]));
			}

			double_t(const std::initializer_list<T>& list)
			: double_t(copy, list.begin(), list.size()) {}

			double_t(const double_t& other)
			: double_t()
			{
				for (const T& data : other)
					this->emplace_back(data);
			}

			double_t& operator=(const double_t& other)
			{
				while (m_Size > other.m_Size)
					this->pop_back();

				auto other_it = other.begin();
				for (T& data : *this)
					data = *(other_it++);

				for (; other_it != other.end(); other_it++)
					this->emplace_back(*other_it);

				return *this;
			}

			inline double_t(double_t&& other)
			{
				memcpy(this, &other, sizeof(double_t));
				memset(&other, 0, sizeof(double_t));
			}

			inline double_t& operator=(double_t&& other)
			{
				this->clear();
				memcpy(this, &other, sizeof(double_t));
				memset(&other, 0, sizeof(double_t));
				return *this;
			}

			template<typename... ArgsT>
			T* emplace_back(ArgsT&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<ArgsT>(__args)...)->data);

				m_Tail = new node_t(nullptr, m_Tail, std::forward<ArgsT>(__args)...);
				return &((m_Tail->previous->next = m_Tail)->data);
			}

			template<typename... ArgsT>
			T* emplace_front(ArgsT&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<ArgsT>(__args)...)->data);

				m_Head = new node_t(m_Head, nullptr, std::forward<ArgsT>(__args)...);
				return &((m_Head->next->previous = m_Head)->data);
			}

			template<typename... ArgsT>
			T* emplace_at(size_t index, ArgsT&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<ArgsT>(__args)...)->data);

				if (index >= m_Size)
				{
					m_Tail = new node_t(nullptr, m_Tail, std::forward<ArgsT>(__args)...);
					return &((m_Tail->previous->next = m_Tail)->data);
				}

				node_t* node = this->at(index).node;
				node = new node_t(node, node->previous, std::forward<ArgsT>(__args)...);
				if (node->previous)
					node->previous->next = node;
				return &((node->next->previous = node)->data);
			}

			bool pop_back(void)
			{
				if (!m_Head)
					return false;

				m_Size--;
				if (m_Tail = m_Tail->previous)
				{
					delete m_Tail->next;
					m_Tail->next = nullptr;
				} else
				{
					delete m_Head;
					m_Head = nullptr;
				}
				return true;
			}

			bool pop_front(void)
			{
				if (!m_Head)
					return false;

				m_Size--;
				if (m_Head = m_Head->next)
				{
					delete m_Head->previous;
					m_Head->previous = nullptr;
				} else
				{
					delete m_Tail;
					m_Tail = nullptr;
				}
				return true;
			}

			bool pop_at(size_t index)
			{
				if (!m_Head)
					return false;

				if (!--m_Size && index)
					return false;

				if (index > m_Size)
					return false;

				node_t* node = this->at(index).node;

				if (!node->is_tail())
					node->next->previous = node->previous;
				else
					m_Tail = node->previous;

				if (!node->is_head())
					node->previous->next = node->next;
				else
					m_Head = node->next;

				delete node;
				return true;
			}

			bool pop(T* data)
			{
				if (!find(data))
					return false;

				node_t* node = (node_t*)((byte_t*)data - 16);
				if (!node->is_tail())
					node->next->previous = node->previous;
				else
					m_Tail = node->previous;

				if (!node->is_head())
					node->previous->next = node->next;
				else
					m_Head = node->next;

				m_Size--;
				delete node;
				return true;
			}

			[[nodiscard]] bool find(const T* data) const
			{
				if (!data) return false;
				for (const T& it : *this)
					if (&it == data)
						return true;
				return false;
			}

			bool swap(node_t* node1, node_t* node2)
			{
				if (!node1 || !node2 || node1 == node2)
					return false;
				
				node_t* temp = node1->next;

				if (node1->next = node2->next)
					node1->next->previous = node1;
				else
					m_Tail = node1;

				if (node2->next = temp)
					node2->next->previous = node2;
				else
					m_Tail = node2;

				temp = node1->previous;

				if (node1->previous = node2->previous)
					node1->previous->next = node1;
				else
					m_Head = node1;

				if (node2->previous = temp)
					node2->previous->next = node2;
				else
					m_Head = node2;

				return true;
			}
			inline bool swap(size_t index1, size_t index2) { return this->swap(this->at(index1).node, this->at(index2).node); }
			inline bool swap(iterator_t it1, iterator_t it2) { return this->swap(it1.node, it2.node); }

			[[nodiscard]] inline iterator_t begin(void) { return m_Head; }
			[[nodiscard]] inline const_iterator_t begin(void) const { return m_Head; }
			[[nodiscard]] inline const_iterator_t cbegin(void) const { return m_Head; }

			[[nodiscard]] inline iterator_t end(void) { return nullptr; }
			[[nodiscard]] inline const_iterator_t end(void) const { return nullptr; }
			[[nodiscard]] inline const_iterator_t cend(void) const { return nullptr; }

			[[nodiscard]] inline reverse_iterator_t rbegin(void) { return m_Tail; }
			[[nodiscard]] inline const_reverse_iterator_t rbegin(void) const { return m_Tail; }
			[[nodiscard]] inline const_reverse_iterator_t crbegin(void) const { return m_Tail; }

			[[nodiscard]] inline reverse_iterator_t rend(void) { return nullptr; }
			[[nodiscard]] inline const_reverse_iterator_t rend(void) const { return nullptr; }
			[[nodiscard]] inline const_reverse_iterator_t crend(void) const { return nullptr; }

			[[nodiscard]] iterator_t at(size_t index)
			{
				if (index > m_Size * 0.5)
					return iterator_t(m_Tail, m_Size - index - 1, backwards);
				return iterator_t(m_Head, index, forward);
			}
			[[nodiscard]] const_iterator_t at(size_t index) const
			{
				if (index > m_Size * 0.5)
					return const_iterator_t(m_Tail, m_Size - index - 1, backwards);
				return const_iterator_t(m_Head, index, forward);
			}

			[[nodiscard]] inline T& operator[](size_t index) { return *(this->at(index)); }
			[[nodiscard]] inline const T& operator[](size_t index) const { return *(this->at(index)); }

			[[nodiscard]] inline T& head(void) { return *m_Head; }
			[[nodiscard]] inline const T& head(void) const { return *m_Head; }

			[[nodiscard]] inline T& tail(void) { return *m_Tail; }
			[[nodiscard]] inline const T& tail(void) const { return *m_Tail; }

			[[nodiscard]] inline size_t size(void) { return m_Size; }
			[[nodiscard]] inline size_t empty(void) { return !m_Size; }
		private:
			template<typename... ArgsT>
			node_t* _emplace_empty(ArgsT&&... __args)
			{
				m_Head = new node_t(nullptr, nullptr, std::forward<ArgsT>(__args)...);
				return m_Tail = m_Head;
			}
		private:
			node_t* m_Head,* m_Tail;
			size_t m_Size;
		};
	} // namespace list

	template<typename T>
	using double_list_t = list::double_t<T>;

	template<typename T>
	using double_list_node_t = list::double_t<T>::node_t;

} // namespace neo

#endif // NEO_LINKED_LIST_HPP