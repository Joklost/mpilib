#ifndef MANETSIMS_HW_H
#define MANETSIMS_HW_H

#include <iostream>

#include <mpilib/mpi.h>

#include "hwglobals.h"


namespace hardware {

    /**
     * Add execution time to our localtime.
     * @private
     */
    void prepare_localtime(std::chrono::microseconds duration);

    /**
     * Gets the current execution time.
     * @return std::chrono::time_point
     * @private
     */
    std::chrono::time_point<std::chrono::high_resolution_clock> now();

    /**
     * Initialise the hardware interface.
     *
     * @param loc The initial geolocation of this node.
     * @param debug Enable debug logging.
     */
    void init(bool debug = false);

    /**
     * Deinitialise the hardware interface.
     */
    void deinit();

    /**
     * Get the unique identifer assigned to this node.
     * @return unsigned long, identifier.
     */
    unsigned long get_id();

    /**
     * Get the rank assigned to this node by the MPI.
     * @return unsigned long, rank assigned by MPI.
     */
    unsigned long get_world_rank();

    /**
     * Get the size of the known world (the amount of nodes).
     * @return unsigned long, world size.
     */
    unsigned long get_world_size();

    /**
     * Get the current local time.
     * @return std::chrono::microseconds, localtime.
     */
    std::chrono::microseconds get_localtime();

    /**
     * Report the local time of this node to the controller.
     *
     * This can be called as an alternative to #broadcast, #listen, or #sleep,
     * if none is applicable.
     */
    void report_localtime();

    /**
     * Broadcast a blob of data.
     * @param data std::vector containing data to broadcast.
     * @return std::chrono::microseconds, amount of microseconds broadcast took.
     */
    std::chrono::microseconds broadcast(const std::vector<octet>& data);

    /**
     * Listen for packets for the given duration.
     * @param duration Amount of microseconds to listen for.
     * @return std::vector, containing std::vectors of data.
     */
    std::vector<octet> listen(std::chrono::microseconds duration);

    /**
     * Sleep for the given duration.
     * @param duration Amount of microseconds to sleep for.
     */
    void sleep(std::chrono::microseconds duration);
}

#endif /* MANETSIMS_HW_H */
