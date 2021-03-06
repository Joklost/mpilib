cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_CXX_STANDARD 14)

project(mpilib LANGUAGES C CXX VERSION 1.0)

add_subdirectory(libs)

add_library(mpilib STATIC
        src/mpi.cpp
        src/hardware.cpp
        src/ostr.cpp
        src/helpers.cpp
        src/hwglobals.cpp
        src/interface.cpp)

set_target_properties(mpilib PROPERTIES LINKER_LANGUAGE CXX)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(mpilib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src test)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS mpilib EXPORT MPILibLibraryConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(mpilib spdlog mpich common)
