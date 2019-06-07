#ifndef MANETSIMS_INTERFACE_H
#define MANETSIMS_INTERFACE_H

#include "hardware.h"

namespace hardware {
    void broadcast(const std::vector<octet> &data);

    std::vector<octet> receive(std::chrono::microseconds duration);

    void sleep(std::chrono::microseconds duration);

    void inform();
}


#endif //MANETSIMS_INTERFACE_H
