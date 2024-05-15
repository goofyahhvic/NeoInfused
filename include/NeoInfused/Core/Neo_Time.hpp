#if !defined(NEO_TIME_HPP)
#define NEO_TIME_HPP

#include <ctime>
#include <string>

namespace neo {
    namespace core {
        class Time {
            Time(void) = default;
            ~Time(void) = default;
        public:
            static std::string GetHoursMinutesSeconds(void);

        private:
            static std::time_t sm_Seconds;
        };

    } // namespace core
    
} // namespace neo

#endif // NEO_TIME_HPP