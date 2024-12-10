#if !defined(INF_CORE_HPP)
#define INF_CORE_HPP

#include <stdint.h>

namespace inf {
	union color32_t {
		struct { uint8_t r, g, b, a; };
		uint32_t rgba;
	};
}

#endif // INF_CORE_HPP