#if !defined(INF_ERROR_TYPES_HPP)
#define INF_ERROR_TYPES_HPP

enum inf_ErrorType : uint16_t {
	INF_ERROR_NONE = 0, INF_GLFW_ERROR
};

namespace inf {
	using ErrorType = inf_ErrorType;
	typedef void (*ErrorCallbackFn)(ErrorType error_type, const char* msg, void* data);
}

#endif // INF_ERROR_TYPES_HPP