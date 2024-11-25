#if !defined(NEO_DOUBLE_ITERATOR_HPP)
#define NEO_DOUBLE_ITERATOR_HPP

namespace neo {
	namespace list {
		enum forward_t { forward };
		enum backwards_t { backwards };

		template<typename ListT>
		class double_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = double_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int) { node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator--(void) { node = node->previous; return *this; }
			inline this_t  operator--(int) { node_t* temp = node; node = node->previous; return temp; }

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
			inline double_iterator_t(node_t* node = nullptr)
			: node(node) {}

			inline double_iterator_t(node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline double_iterator_t(node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			node_t* node;
		};

		template<typename ListT>
		class double_const_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = double_const_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->next; return *this; }
			inline this_t  operator++(int) { const node_t* temp = node; node = node->next; return temp; }

			inline this_t& operator--(void) { node = node->previous; return *this; }
			inline this_t  operator--(int) { const node_t* temp = node; node = node->previous; return temp; }

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

			inline double_const_iterator_t(const node_t* node = nullptr)
			: node(node) {}

			inline double_const_iterator_t(const node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline double_const_iterator_t(const node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			const node_t* node;
		};

		template<typename ListT>
		class double_reverse_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = double_reverse_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->previous; return *this; }
			inline this_t  operator++(int) { node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator--(void) { node = node->next; return *this; }
			inline this_t  operator--(int) { node_t* temp = node; node = node->next; return temp; }

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

			inline double_reverse_iterator_t(node_t* node = nullptr)
			: node(node) {}

			inline double_reverse_iterator_t(node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline double_reverse_iterator_t(node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			node_t* node;
		};

		template<typename ListT>
		class double_const_reverse_iterator_t {
		public:
			using T = ListT::T_t;
			using node_t = ListT::node_t;
			using this_t = double_const_reverse_iterator_t;
		public:
			inline this_t& operator++(void) { node = node->previous; return *this; }
			inline this_t  operator++(int) { const node_t* temp = node; node = node->previous; return temp; }

			inline this_t& operator--(void) { node = node->next; return *this; }
			inline this_t  operator--(int) { const node_t* temp = node; node = node->next; return temp; }

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

			inline double_const_reverse_iterator_t(const node_t* node = nullptr)
			: node(node) {}

			inline double_const_reverse_iterator_t(const node_t* node, size_t amount, forward_t)
			: node(node) { *this += amount; }

			inline double_const_reverse_iterator_t(const node_t* node, size_t amount, backwards_t)
			: node(node) { *this -= amount; }

			const node_t* node;
		};
	} // namespace list
} // namespace neo

#endif // NEO_DOUBLE_ITERATOR_HPP