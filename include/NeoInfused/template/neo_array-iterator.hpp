#if !defined(NEO_ARRAY_ITERATOR_HPP)
#define NEO_ARRAY_ITERATOR_HPP

namespace neo {
	namespace array {
		template<typename ArrayT>
		class iterator_t {
			using T = ArrayT::T_t;
			using this_t = iterator_t<ArrayT>;
		public:
			inline this_t& operator++(void) { m_Ptr++; return *this; }
			inline this_t  operator++(int) { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator--(void) { m_Ptr--; return *this; }
			inline this_t  operator--(int) { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr += amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr + amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr - amount); }

			[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayT::reverse_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return m_Ptr <=> other.m_Ptr; }

			iterator_t(T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			T* m_Ptr;
		};

		template<typename ArrayT>
		class reverse_iterator_t {
			using T = ArrayT::T_t;
			using this_t = reverse_iterator_t<ArrayT>;
		public:
			inline this_t& operator++(void) { m_Ptr--; return *this; }
			inline this_t  operator++(int) { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator--(void) { m_Ptr++; return *this; }
			inline this_t  operator--(int) { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr += amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr - amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr + amount); }

			[[nodiscard]] inline T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayT::iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return other.m_Ptr <=> m_Ptr; }

			reverse_iterator_t(T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			T* m_Ptr;
		};

		template<typename ArrayT>
		class const_iterator_t {
			using T = ArrayT::T_t;
			using this_t = const_iterator_t<ArrayT>;
		public:
			inline this_t& operator++(void) { m_Ptr++; return *this; }
			inline this_t  operator++(int) { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator--(void) { m_Ptr--; return *this; }
			inline this_t  operator--(int) { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr += amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr -= amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr + amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr - amount); }

			[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline const T& operator*(void) const { return *m_Ptr; }
			[[nodiscard]] inline const T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayT::const_reverse_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other) const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return m_Ptr <=> other.m_Ptr; }

			const_iterator_t(const T* const ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			const T* m_Ptr;
		};

		template<typename ArrayT>
		class const_reverse_iterator_t {
			using T = ArrayT::T_t;
			using this_t = const_reverse_iterator_t<ArrayT>;
		public:
			inline this_t& operator++(void) { m_Ptr--; return *this; }
			inline this_t  operator++(int) { m_Ptr--; return this_t(m_Ptr + 1); }

			inline this_t& operator--(void) { m_Ptr++; return *this; }
			inline this_t  operator--(int) { m_Ptr++; return this_t(m_Ptr - 1); }

			inline this_t& operator+=(size_t amount) { m_Ptr -= amount; return *this; }
			inline this_t& operator-=(size_t amount) { m_Ptr += amount; return *this; }

			[[nodiscard]] inline this_t operator+(size_t amount) const { return this_t(m_Ptr - amount); }
			[[nodiscard]] inline this_t operator-(size_t amount) const { return this_t(m_Ptr + amount); }

			[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }
			[[nodiscard]] inline const T& operator*(void)  const { return *m_Ptr; }
			[[nodiscard]] inline const T* get(void) { return m_Ptr; }
			[[nodiscard]] inline ArrayT::const_iterator_t reverse(void) { return m_Ptr; }

			[[nodiscard]] inline bool operator==(const this_t& other)  const { return m_Ptr == other.m_Ptr; }
			[[nodiscard]] inline auto operator<=>(const this_t& other) const { return other.m_Ptr <=> m_Ptr; }

			const_reverse_iterator_t(const T* ptr = nullptr)
			: m_Ptr(ptr) {}
		private:
			const T* m_Ptr;
		};
	} // namespace array
} // namespace neo

#endif // NEO_ARRAY_ITERATOR_HPP