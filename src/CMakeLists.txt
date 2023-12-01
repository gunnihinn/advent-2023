enable_testing()

add_subdirectory(advent)
include_directories(advent)

add_subdirectory(01)

add_executable(hello advent main.cpp)
add_executable(test.hello advent test.cpp)

target_link_libraries(hello advent)

include(GoogleTest)
target_link_libraries(test.hello PRIVATE advent)
link_fuzztest(test.hello)
gtest_discover_tests(test.hello)

install(TARGETS hello DESTINATION bin)
