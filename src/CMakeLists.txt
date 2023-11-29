add_subdirectory(advent)
include_directories(advent)

add_executable(hello advent main.cpp)

target_link_libraries(hello advent)

install(TARGETS hello DESTINATION bin)
