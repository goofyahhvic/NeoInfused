#if !defined(INF_HELLO_WORLD_HPP)
#define INF_HELLO_WORLD_HPP

namespace inf {
	typedef void (*HelloWorld)(void);
	inline HelloWorld hello_world = nullptr;
	void init(void);
}

#endif // INF_HELLO_WORLD_HPP