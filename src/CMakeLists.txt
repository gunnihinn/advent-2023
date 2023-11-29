enable_testing()

add_subdirectory(advent)
include_directories(advent)

add_executable(hello advent main.cpp)
add_executable(test.hello advent test.cpp)

target_link_libraries(hello advent)
target_link_libraries(test.hello GTest::gtest_main advent)

include(GoogleTest)
gtest_discover_tests(test.hello)

install(TARGETS hello DESTINATION bin)
