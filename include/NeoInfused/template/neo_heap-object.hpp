#if !defined(NEO_HEAP_OBJECT_HPP)
#define NEO_HEAP_OBJECT_HPP

#include "../neo_core.hpp"

namespace neo {
	template<typename T>
	class heap_object_t {
	public:
		inline heap_object_t(void*)
		: m_Ptr(nullptr) {}

		template<typename... ArgsT>
		inline heap_object_t(ArgsT&&... __args)
		: m_Ptr(new T(std::forward<ArgsT>(__args)...)) {}

		inline ~heap_object_t(void) { this->destroy(); }

		inline void destroy(void) { delete m_Ptr; m_Ptr = nullptr; }

		inline heap_object_t(const heap_object_t& other)
		: m_Ptr(new T(*other)) {}

		heap_object_t& operator=(const heap_object_t& other)
		{
			delete m_Ptr;
			m_Ptr = new T(*other);
			return *this;
		}

		inline heap_object_t(heap_object_t&& other)
		: m_Ptr(std::exchange(other.m_Ptr, nullptr)) {}

		heap_object_t& operator=(heap_object_t&& other)
		{
			delete m_Ptr;
			m_Ptr = std::exchange(other.m_Ptr, nullptr);
			return *this;
		}

		[[nodiscard]] inline size_t size(void) { return sizeof(T); }

		[[nodiscard]] inline T* operator->(void) { return m_Ptr; }
		[[nodiscard]] inline const T* operator->(void) const { return m_Ptr; }

		[[nodiscard]] inline T& operator*(void) { return *m_Ptr; }
		[[nodiscard]] inline const T& operator*(void) const { return *m_Ptr; }

		[[nodiscard]] inline T* ptr(void) { return m_Ptr; }
		[[nodiscard]] inline const T* ptr(void) const { return m_Ptr; }

		[[nodiscard]] inline T& get(void) { return *m_Ptr; }
		[[nodiscard]] inline const T& get(void) const { return *m_Ptr; }

		[[nodiscard]] inline bool operator==(const heap_object_t& other)  const { return m_Ptr == other.m_Ptr; }
		[[nodiscard]] inline auto operator<=>(const heap_object_t& other) const { return other.m_Ptr <=> m_Ptr; }

		[[nodiscard]] inline bool operator==(const T* other)  const { return m_Ptr == other; }
		[[nodiscard]] inline auto operator<=>(const T* other) const { return m_Ptr <=> other; }

		[[nodiscard]] inline operator bool(void) const { return m_Ptr; }
	private:
		T* m_Ptr;
	};
}

#endif // NEO_HEAP_OBJECT_HPP