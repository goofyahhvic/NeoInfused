#if !defined(NEO_GRAPHIC_HPP)
#define NEO_GRAPHIC_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
    class Graphic {
    public:
        Graphic(void) {}
        virtual ~Graphic(void) {}

        virtual void draw(void) = 0;
    };
} // namespace neo

#endif // NEO_GRAPHIC_HPP