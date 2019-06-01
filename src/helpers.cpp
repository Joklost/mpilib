#include <cmath>

#include <mpilib/helpers.h>

std::string mpilib::processor_name(const char *processor_name, int world_rank) {
    auto sid = std::string(4 - std::to_string(world_rank).length(), '0') + std::to_string(world_rank);
    return std::string{processor_name} + sid;
}

std::chrono::microseconds mpilib::compute_transmission_time(unsigned long baudrate, unsigned long octets) {
    return std::chrono::microseconds(static_cast<unsigned long>((1.0 / baudrate) * (octets * 8) * 1000 * 1000));
}

std::string mpilib::format_duration(std::chrono::microseconds us) {
    auto dur = break_down_durations<std::chrono::seconds, std::chrono::milliseconds, std::chrono::microseconds>(us);
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::get<0>(dur).count()
        << "::"
        << std::setw(3)
        << std::get<1>(dur).count()
        << "::"
        << std::setw(3)
        << std::get<2>(dur).count();
    return oss.str();
}

