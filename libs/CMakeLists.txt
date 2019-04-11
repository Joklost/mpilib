if (NOT TARGET spdlog)
    add_subdirectory(spdlog)
endif()

if (NOT TARGET common)
    add_subdirectory(common)
endif()