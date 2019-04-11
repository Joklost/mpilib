#include <string>

#include <mpilib/hwglobals.h>

std::chrono::time_point<std::chrono::high_resolution_clock> hardware::clock{}; // NOLINT(cert-err58-cpp)
std::chrono::microseconds hardware::localtime{};

std::shared_ptr<spdlog::logger> hardware::logger = nullptr;
bool hardware::initialized{};
unsigned long hardware::id{};
unsigned long hardware::world_size{};
unsigned long hardware::world_rank{};
std::string hardware::processor_name{};
