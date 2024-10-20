#if !defined(NEO_PCH_HPP)
#define NEO_PCH_HPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <exception>
#include <stdexcept>
#include <filesystem>
#include <format>
#include <chrono>
#include <thread>
#include <limits>

#include <initializer_list>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <tuple>
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

#if defined(NEO_PLATFORM_WINDOWS)
	#include <Windows.h>
#elif defined(NEO_PLATFORM_LINUX)
	#include <dlfcn.h>
#endif // NEO_PLATFORM_WINDOWS

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#endif // NEO_PCH_HPP