#include "Neo_PCH.hpp"
#include "./Neo_Time.hpp"

namespace neo {
    namespace core {
        std::time_t Time::sm_Seconds;

        std::string Time::GetHoursMinutesSeconds(void) {
            sm_Seconds = std::time(nullptr);
            std::string str(std::asctime(std::localtime(&sm_Seconds)));
            str = str.substr(10, 10);
            str[0] = '[';
            str[str.length()-1] = ']';
            return str;
        }
        
    } // namespace core
    
} // namespace neo
