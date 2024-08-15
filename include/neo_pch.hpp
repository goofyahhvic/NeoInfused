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

#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#if defined(NEO_PLATFORM_WINDOWS)
#include <windows.h>
#endif // NEO_PLATFORM_WINDOWS

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#endif // NEO_PCH_HPP