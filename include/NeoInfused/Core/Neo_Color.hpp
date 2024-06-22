#if !defined(NEO_COLOR_HPP)
#define NEO_COLOR_HPP

// F for Font
// B for Background
#define NEO_COLOR_RSET  "\x1B[0m"         // reset color
#define NEO_COLOR_FRED  "\x1B[31m"        // red
#define NEO_COLOR_BRED  "\x1B[0m\033[41m" // red
#define NEO_COLOR_FGRN  "\x1B[32m"        // green 
#define NEO_COLOR_FYEL  "\x1B[33m"        // yellow
#define NEO_COLOR_FBLU  "\x1B[34m"        // blue
#define NEO_COLOR_FMAG  "\x1B[35m"        // magenta
#define NEO_COLOR_FCYN  "\x1B[36m"        // cyan
#define NEO_COLOR_FWHT  "\x1B[37m"        // white

#define NEO_FONT_BOLD "\x1B[1m"           // bold
#define NEO_FONT_UNDL "\x1B[4m"           // underline

namespace neo {
    union Color {
        struct { uint8_t r, g, b, a; };
        uint32_t rgba = 0x000000FF;
        operator SDL_Color(void) { return {r, g, b, a}; }
    };
} // namespace neo

#define NEO_COLOR_BLACK {0,   0,   0,   255}
#define NEO_COLOR_RED   {255, 0,   0,   255}
#define NEO_COLOR_YEL   {255, 255, 0,   255}
#define NEO_COLOR_PURPL {255, 0,   255, 255}
#define NEO_COLOR_GREEN {0,   255, 0,   255}
#define NEO_COLOR_CYAN  {0,   255, 255, 255}
#define NEO_COLOR_BLUE  {0,   0,   255, 255}
#define NEO_COLOR_WHITE {255, 255, 255, 255}

#endif // NEO_COLOR_HPP