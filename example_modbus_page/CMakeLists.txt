cmake_minimum_required(VERSION 3.1)
project(example_modbus_page)

set(CMAKE_C_STANDARD 11)

# Add the include directories for modbus_page_map.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the source files for the executable
add_executable(page_mapper
    page_mapper.c
    src/modbus_page_map.c
)
# Link any libraries that the executable needs
target_link_libraries(page_mapper
    # list any libraries here, e.g.:
    # pthread
)
