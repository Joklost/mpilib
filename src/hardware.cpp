#include <mpilib/hardware.h>

void hardware::init(bool debug) {
    if (hardware::initialized) {
        return;
    }

    hardware::initialized = true;

    int name_len{};
    char name[MPI_MAX_PROCESSOR_NAME];
    int size{};
    int rank{};
    mpi::init(&size, &rank, &name_len, name);

    if (size <= 2) {
        mpi::deinit();
        throw std::runtime_error("node count too low, unable to run simulation");
    }

    hardware::world_size = size - 1;
    hardware::world_rank = rank;
    hardware::processor_name = mpilib::processor_name(name, hardware::world_rank);
    hardware::logger = spdlog::stdout_color_mt(hardware::processor_name);
    if (debug) {
        hardware::logger->set_level(spdlog::level::debug);
    } else {
        hardware::logger->set_pattern("%v");
    }

    hardware::logger->debug("init()");

    /* Handshake */
    hardware::id = mpi::recv<unsigned long>(CTRLR, HANDSHAKE);
    if (mpi::send(hardware::world_rank, CTRLR, HANDSHAKE) == MPI_SUCCESS) {
        /* Wait for ready signal from Coordinator. */
        mpi::recv<unsigned long>(CTRLR, READY);
        hardware::clock = hardware::now();
        hardware::localtime = 0us;
    } else {
        mpi::deinit();
        return;
    }
}

void hardware::deinit() {
    if (!hardware::initialized) {
        return;
    }

    hardware::logger->debug("deinit()");
    hardware::prepare_localtime(0us);
    mpi::send(static_cast<unsigned long>(hardware::localtime.count()), CTRLR, DIE);
    mpi::deinit();
    hardware::initialized = false;
}

void hardware::transmit(const std::vector<octet> &data) {
    if (!hardware::initialized) {
        return;
    }

    if (data.empty()) {
        return;
    }

    auto duration = mpilib::compute_transmission_time(BAUDRATE, data.size());
    hardware::prepare_localtime(duration);
    hardware::logger->debug("transmit(octets={}, localtime={}, duration={})",
                            data.size(), hardware::localtime - duration, duration);
    mpi::send((hardware::localtime - duration).count(), CTRLR, TX_PKT);
    mpi::send(data, CTRLR, TX_PKT_DATA);

    hardware::clock = hardware::now();
}

std::vector<octet> hardware::receive(std::chrono::microseconds duration) {
    if (!hardware::initialized) {
        return std::vector<octet>{};
    }

    if (duration < 0us) {
        return std::vector<octet>{};
    }

    hardware::prepare_localtime(duration);
    hardware::logger->debug("receive(localtime={}, duration={})", hardware::localtime - duration, duration);

    /* Let the ctrlr know that we want to listen for a number of time slots. */
    mpi::send((hardware::localtime - duration).count(), CTRLR, RX_PKT);
    mpi::send(duration.count(), CTRLR, RX_PKT_DURATION);

    /* Wait for ctrlr to respond with number of packets. */
    hardware::localtime = std::chrono::microseconds{mpi::recv<unsigned long>(CTRLR, RX_PKT_END)};
    auto packet = mpi::recv<std::vector<octet>>(CTRLR, RX_PKT_DATA);

    hardware::clock = hardware::now();
    return packet;
}

void hardware::noop(std::chrono::microseconds duration) {
    if (!hardware::initialized) {
        return;
    }

    if (duration < 0us) {
        return;
    }

    hardware::prepare_localtime(duration);
    hardware::logger->debug("noop(localtime={}, duration={})", hardware::localtime - duration, duration);

    if (duration == 0us) {
        mpi::send(static_cast<unsigned long>(hardware::localtime.count()), CTRLR, INFORM);
    } else {
        mpi::send(static_cast<unsigned long>(hardware::localtime.count() - duration.count()), CTRLR, SLEEP);
        mpi::send(static_cast<unsigned long>(duration.count()), CTRLR, SLEEP_DURATION);
    }

    hardware::clock = hardware::now();
}

unsigned long hardware::get_id() {
    if (!hardware::initialized) {
        return 0;
    }

    return hardware::id;
}

unsigned long hardware::get_world_rank() {
    if (!hardware::initialized) {
        return 0;
    }

    return hardware::world_rank;
}

unsigned long hardware::get_world_size() {
    if (!hardware::initialized) {
        return 0;
    }

    return hardware::world_size;
}

std::chrono::time_point<std::chrono::high_resolution_clock> hardware::now() {
    return std::chrono::high_resolution_clock::now();
}

void hardware::prepare_localtime(std::chrono::microseconds duration) {
    /* Add execution time since last action to our localtime. */
    auto now = hardware::now();
    hardware::localtime = std::chrono::duration_cast<std::chrono::microseconds>(
            (now - hardware::clock) + hardware::localtime + duration
    );
}

std::chrono::microseconds hardware::get_localtime() {
    hardware::prepare_localtime(0us);
    hardware::clock = hardware::now();
    return hardware::localtime;
}
