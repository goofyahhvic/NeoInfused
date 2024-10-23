#if !defined(INF_ERROR_TYPES_HPP)
#define INF_ERROR_TYPES_HPP

enum inf_error_type_t : uint16_t {
	INF_ERROR_NONE = 0, INF_GLFW_ERROR
};

namespace inf {
	namespace error {
		using type_t = inf_error_type_t;
		typedef void (*callback_fn)(type_t error_type, const char* msg, void* data);
	}
}

#endif // INF_ERROR_TYPES_HPP