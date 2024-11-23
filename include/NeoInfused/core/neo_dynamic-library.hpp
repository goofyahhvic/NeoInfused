#if !defined(NEO_DYNAMIC_LIBRARY_HPP)
#define NEO_DYNAMIC_LIBRARY_HPP

#include "../neo_core.hpp"

namespace neo {
	class dll_t {
	public:
		inline dll_t(void) { m_Handle = nullptr; }
		inline dll_t(const char* name) { this->load(name); }
		inline dll_t(const wchar_t* name) { this->load(name); }
		inline ~dll_t(void) { this->unload(); }

		void load(const wchar_t* name);
		void load(const char* name);
		void unload(void);

		void* fn(const char* name) const;
		template<typename FnT>
		inline FnT fn(const char* name) const { return (FnT)this->fn(name); }

		inline operator bool(void) const { return m_Handle; }
		inline const std::string& name(void) const { return m_Name; }
		inline void* handle(void) { return m_Handle; }
	private:
		void* m_Handle = nullptr;
		std::string m_Name;
	};
	using dynamic_library_t = dll_t;
} // namespace neo

#endif // NEO_DYNAMIC_LIBRARY_HPP