enable_testing()

add_executable(test.hello test.cpp)
target_link_libraries(test.hello GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test.hello)
