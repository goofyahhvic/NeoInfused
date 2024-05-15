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

#endif // NEO_COLOR_HPP