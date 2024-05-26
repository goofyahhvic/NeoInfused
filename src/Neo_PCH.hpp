#if !defined(NEO_PCH_HPP)
#define NEO_PCH_HPP

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cstdbool>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <functional>
#include <exception>
#include <filesystem>

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
#endif // NEO_PLATFORM_LINUX

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <format>
#include <glm/glm.hpp>
#include "NeoInfused/Core/Neo_Color.hpp"

#include "NeoInfused/Core/Neo_Time.hpp"
#include "NeoInfused/Core/Neo_Core.hpp"

#endif // NEO_PCH_HPP