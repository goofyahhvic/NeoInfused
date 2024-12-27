#if !defined(INF_CORE_HPP)
#define INF_CORE_HPP

#include <stdint.h>

enum inf_shader_stage_t : uint8_t {
	INF_SHADER_STAGE_NONE = 0,
	INF_SHADER_STAGE_VERTEX,
	INF_SHADER_STAGE_FRAGMENT,
	INF_SHADER_STAGE_PIXEL = INF_SHADER_STAGE_FRAGMENT,
	INF_SHADER_STAGE_LAST = INF_SHADER_STAGE_FRAGMENT
};

namespace inf {
	namespace shader {
		using stage_t = inf_shader_stage_t;
	} // namespace shader
	using shader_stage_t = shader::stage_t;

	union color32_t {
		struct { uint8_t r, g, b, a; };
		uint32_t rgba;
	};
} // namespace inf

#endif // INF_CORE_HPP