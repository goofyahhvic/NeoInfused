#include "Neo_PCH.hpp"
#include "NeoInfused/Core/Neo_Time.hpp"

namespace neo {
    namespace core {
        std::time_t Time::s_Seconds;

        std::string Time::GetHoursMinutesSeconds(void) {
            Time::s_Seconds = std::time(nullptr);
            std::string str(std::asctime(std::localtime(&Time::s_Seconds)));
            str = str.substr(10, 10);
            str[0] = '[';
            str[str.length()-1] = ']';
            return str;
        }
        
    } // namespace core
    
} // namespace neo
