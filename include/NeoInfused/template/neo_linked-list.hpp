#if !defined(NEO_LINKED_LIST_HPP)
#define NEO_LINKED_LIST_HPP

#include "../neo_core.hpp"

namespace neo {
	namespace list {
		enum forward_t { forward };
		enum backwards_t { backwards };
		enum copy_t { copy };
		enum move_t { move };

		template<typename ListT>
		class iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int)  { node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator--(void) { node = node->previous; return *this; }
			inline this_t  operator--(int)  { node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			inline this_t& operator-=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					--(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }
			[[nodiscard]] inline this_t operator-(size_t amount) const { this_t it(node); return it -= amount; }

			[[nodiscard]] inline T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline T& operator*(void) const { return node->data; }
			[[nodiscard]] inline T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			[[nodiscard]] inline ListT::reverse_iterator_t reverse(void) { return node; }

			inline iterator_t(node_t* node = nullptr)
			: node(node) {}

			inline iterator_t(node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline iterator_t(node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			node_t* node;
		};

		template<typename ListT>
		class const_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = const_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int)  { const node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator--(void) { node = node->previous; return *this; }
			inline this_t  operator--(int)  { const node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			inline this_t& operator-=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					--(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }
			[[nodiscard]] inline this_t operator-(size_t amount) const { this_t it(node); return it -= amount; }

			[[nodiscard]] inline const T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline const T& operator*(void) const { return node->data; }
			[[nodiscard]] inline const T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			[[nodiscard]] inline ListT::const_reverse_iterator_t reverse(void) { return node; }

			inline const_iterator_t(const node_t* node = nullptr)
			: node(node) {}

			inline const_iterator_t(const node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline const_iterator_t(const node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			const node_t* node;
		};

		template<typename ListT>
		class reverse_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = reverse_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->previous; return *this; }
			inline this_t  operator++(int)  { node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator--(void) { node = node->next; return *this; }
			inline this_t  operator--(int)  { node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					--(*this);
				return *this;
			}

			inline this_t& operator-=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }
			[[nodiscard]] inline this_t operator-(size_t amount) const { this_t it(node); return it -= amount; }

			[[nodiscard]] inline T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline T& operator*(void) const { return node->data; }
			[[nodiscard]] inline T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			[[nodiscard]] inline ListT::iterator_t reverse(void) { return node; }

			inline reverse_iterator_t(node_t* node = nullptr)
			: node(node) {}

			inline reverse_iterator_t(node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline reverse_iterator_t(node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			node_t* node;
		};

		template<typename ListT>
		class const_reverse_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = const_reverse_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->previous; return *this; }
			inline this_t  operator++(int)  { const node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator--(void) { node = node->next; return *this; }
			inline this_t  operator--(int)  { const node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					--(*this);
				return *this;
			}

			inline this_t& operator-=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }
			[[nodiscard]] inline this_t operator-(size_t amount) const { this_t it(node); return it -= amount; }

			[[nodiscard]] inline const T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline const T& operator*(void) const { return node->data; }
			[[nodiscard]] inline const T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			[[nodiscard]] inline ListT::const_iterator_t reverse(void) { return node; }

			inline const_reverse_iterator_t(const node_t* node = nullptr)
			: node(node) {}

			inline const_reverse_iterator_t(const node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline const_reverse_iterator_t(const node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			const node_t* node;
		};

		template<typename T>
		class list_t {
		public:
			struct node_t {
				template<typename... _Args>
				node_t(node_t* next, node_t* previous, _Args&&... __args)
				: next(next), previous(previous), data(std::forward<_Args>(__args)...) {}

				node_t* next,* previous;
				T data;
			};

			using iterator_t = iterator_t<list_t>;
			using const_iterator_t = const_iterator_t<list_t>;
			using reverse_iterator_t = reverse_iterator_t<list_t>;
			using const_reverse_iterator_t = const_reverse_iterator_t<list_t>;
			using T_t = T;
		public:
			inline list_t(void) : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}
			inline ~list_t(void) { clear(); }

			list_t(copy_t, const T* buffer, size_t size)
			: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
			{
				while (m_Size < size)
					this->emplace_back(buffer[m_Size]);
			}

			list_t(move_t, T* buffer, size_t size)
			: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
			{
				while (m_Size < size)
					this->emplace_back(std::move(buffer[m_Size]));
			}

			list_t(const std::initializer_list<T>& list)
			: list_t(copy, list.begin(), list.size()) {}

			list_t(const list_t& other)
			: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
			{
				for (const T& data : other)
					this->emplace_back(data);
			}

			list_t& operator=(const list_t& other)
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

			inline list_t(list_t&& other)
			{
				memcpy(this, &other, sizeof(list_t));
				memset(&other, 0, sizeof(list_t));
			}

			inline list_t& operator=(list_t&& other)
			{
				this->clear();
				memcpy(this, &other, sizeof(list_t));
				memset(&other, 0, sizeof(list_t));
				return *this;
			}

			template<typename... _Args>
			T* emplace_back(_Args&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<_Args>(__args)...)->data);

				m_Tail = new node_t(nullptr, m_Tail, std::forward<_Args>(__args)...);
				return &((m_Tail->previous->next = m_Tail)->data);
			}

			template<typename... _Args>
			T* emplace_front(_Args&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<_Args>(__args)...)->data);

				m_Head = new node_t(m_Head, nullptr, std::forward<_Args>(__args)...);
				return &((m_Head->next->previous = m_Head)->data);
			}

			template<typename... _Args>
			T* emplace_at(size_t index, _Args&&... __args)
			{
				if (!m_Size++)
					return &(this->_emplace_empty(std::forward<_Args>(__args)...)->data);

				if (index >= m_Size)
				{
					m_Tail = new node_t(nullptr, m_Tail, std::forward<_Args>(__args)...);
					return &((m_Tail->previous->next = m_Tail)->data);
				}

				node_t* node = this->at(index).node;
				node = new node_t(node, node->previous, std::forward<_Args>(__args)...);
				if (node->previous)
					node->previous->next= node;
				return &((node->next->previous= node)->data);
			}

			void pop_back(void)
			{
				if (!m_Head)
					return;

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
			}

			void pop_front(void)
			{
				if (!m_Head)
					return;

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
			}

			void pop_at(size_t index)
			{
				if (!m_Head)
					return;

				if (!--m_Size && index)
					return;

				if (index > m_Size)
					return;

				node_t* node = this->at(index).node;

				if (node->next)
					node->next->previous = node->previous;
				else
					m_Tail = node->previous;

				if (node->previous)
					node->previous->next = node->next;
				else
					m_Head = node->next;

				delete node;
			}

			bool pop(T* data)
			{
				if (!find(data))
					return false;

				node_t* node = (node_t*)((byte_t*)data - 16);
				if (node->next)
					node->next->previous = node->previous;
				else
					m_Tail = node->previous;

				if (node->previous)
					node->previous->next = node->next;
				else
					m_Head = node->next;

				m_Size--;
				delete node;
				return true;
			}

			inline void clear(void) { while (m_Head) this->pop_back(); }

			[[nodiscard]] bool find(const T* data) const
			{
				if (!data) return false;
				for (const T& it : *this)
					if (&it == data)
						return true;
				return false;
			}

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
					return iterator_t(m_Head, index, forward);
				return iterator_t(m_Tail, index, backwards);
			}
			[[nodiscard]] const_iterator_t at(size_t index) const
			{
				if (index > m_Size * 0.5)
					return const_iterator_t(m_Head, index, forward);
				return const_iterator_t(m_Tail, index, backwards);
			}

			[[nodiscard]] T& operator[](size_t index) { return *(this->at(index)); }
			[[nodiscard]] const T& operator[](size_t index) const { return *(this->at(index)); }

			[[nodiscard]] inline T& head(void) { return *m_Head; }
			[[nodiscard]] inline const T& head(void) const { return *m_Head; }

			[[nodiscard]] inline T& tail(void) { return *m_Tail; }
			[[nodiscard]] inline const T& tail(void) const { return *m_Tail; }

			[[nodiscard]] inline size_t size(void) { return m_Size; }
			[[nodiscard]] inline size_t empty(void) { return !m_Size; }
		private:
			template<typename... _Args>
			node_t* _emplace_empty(_Args&&... __args)
			{
				m_Head = new node_t(nullptr, nullptr, std::forward<_Args>(__args)...);
				return m_Tail = m_Head;
			}
		private:
			node_t* m_Head,* m_Tail;
			size_t m_Size;
		};
	} // namespace list
	template<typename T>
	using list_t = list::list_t<T>;
} // namespace neo

#endif // NEO_LINKED_LIST_HPP