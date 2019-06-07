#include <mpilib/interface.h>

void hardware::broadcast(const std::vector<octet> &data) {
    /* Two-phase broadcast. */
    if (data.empty() || data.size() > 255) {
        return;
    }

    /* Phase 1: Send header. */
    hardware::logger->debug("broadcast(phase=1)");
    std::vector<octet> header{};
    header.push_back(0x42);
    header.push_back(static_cast<octet>(data.size()));
    hardware::transmit(header);
    hardware::noop(10ms);

    /* Phase 2: Send data. */
    hardware::logger->debug("broadcast(phase=2)");
    hardware::transmit(data);
}

std::vector<octet> hardware::receive(std::chrono::microseconds duration) {
    /* Two-phase listen. */
    if (duration == 0us) {
        return std::vector<octet>();
    }

    /* Phase 1: Receive header. */
    hardware::logger->debug("receive(phase=1)");
    octet data_size = 0;
    auto header = hardware::listen(duration);
    if (header.size() == 2 && header[0] == 0x42) {
        data_size = header[1];
    } else {
        return std::vector<octet>();
    }

    /* Phase 2: Receive data. */
    hardware::logger->debug("receive(phase=2)");
    auto data = hardware::listen(mpilib::compute_transmission_time(BAUDRATE, data_size) + 20ms);
    return data;
}

void hardware::sleep(std::chrono::microseconds duration) {
    hardware::noop(duration);
}

void hardware::inform() {
    hardware::noop(0us);
}

