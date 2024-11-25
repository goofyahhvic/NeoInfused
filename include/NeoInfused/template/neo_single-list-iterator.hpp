#if !defined(NEO_SINGLE_LIST_ITERATOR_HPP)
#define NEO_SINGLE_LIST_ITERATOR_HPP

namespace neo {
	namespace list {
		template<typename ListT>
		class single_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = single_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int) { node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }

			[[nodiscard]] inline T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline T& operator*(void) const { return node->data; }
			[[nodiscard]] inline T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			inline single_iterator_t(node_t* node = nullptr)
			: node(node) {}

			inline single_iterator_t(node_t* node, size_t amount)
			: node(node) { *this += amount; }

			node_t* node;
		};

		template<typename ListT>
		class single_const_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = single_const_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int) { const node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator+=(size_t amount)
			{
				for (size_t i = 0; i < amount; i++)
					++(*this);
				return *this;
			}

			[[nodiscard]] inline this_t operator+(size_t amount) const { this_t it(node); return it += amount; }

			[[nodiscard]] inline const T* operator->(void) const { return &(node->data); }
			[[nodiscard]] inline const T& operator*(void) const { return node->data; }
			[[nodiscard]] inline const T* get(void) { return &(node->data); }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return node == other.node; }

			inline single_const_iterator_t(const node_t* node = nullptr)
			: node(node) {}

			inline single_const_iterator_t(const node_t* node, size_t amount)
			: node(node) { *this += amount; }

			const node_t* node;
		};
	} // namespace list
} // namespace neo

#endif // NEO_SINGLE_LIST_ITERATOR_HPP