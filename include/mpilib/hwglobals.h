#ifndef MANETSIMS_HWGLOBALS_H
#define MANETSIMS_HWGLOBALS_H

#include <spdlog/spdlog.h>
#include <chrono>

namespace hardware {
    /**
    * @private
    */
    extern std::chrono::time_point<std::chrono::high_resolution_clock> clock;

    /**
    * @private
    */
    extern std::chrono::microseconds localtime;

    /**
    * @private
    */
    extern std::shared_ptr<spdlog::logger> logger;

    /**
    * @private
    */
    extern bool initialized;

    /**
    * @private
    */
    extern unsigned long world_size;

    /**
    * @private
    */
    extern unsigned long world_rank;

    /**
    * @private
    */
    extern unsigned long id;

    /**
     * @private
     */
    extern std::string processor_name;
}


#endif /* MANETSIMS_HWGLOBALS_H */
