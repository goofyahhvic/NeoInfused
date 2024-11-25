#if !defined(NEO_LIST_NODE_HPP)
#define NEO_LIST_NODE_HPP

namespace neo {
	namespace list {
		enum copy_t { copy };
		enum move_t { move };

		template<typename ListT>
		struct single_node_t {
			using T = ListT::T_t;
		public:
			template<typename... ArgsT>
			single_node_t(single_node_t* next, ArgsT&&... __args)
			: next(next), data(std::forward<ArgsT>(__args)...) {}

			inline bool is_tail(void) const { return !next; }

			inline T& operator*(void) { return data; }
			inline const T& operator*(void) const { return data; }
		public:
			single_node_t* next;
			T data;
		};

		template<typename ListT>
		struct double_node_t {
			using T = ListT::T_t;
		public:
			template<typename... ArgsT>
			double_node_t(double_node_t* next, double_node_t* previous, ArgsT&&... __args)
			: next(next), previous(previous), data(std::forward<ArgsT>(__args)...) {}

			inline bool is_head(void) const { return !previous; }
			inline bool is_tail(void) const { return !next; }

			inline T& operator*(void) { return data; }
			inline const T& operator*(void) const { return data; }
		public:
			double_node_t* next,* previous;
			T data;
		};
	} // namespace list
} // namespace neo

#endif // NEO_LIST_NODE_HPP