set(TEST_SOURCES
        TestConstructor.cpp
        Tester.cpp
    )

add_executable(tester ${TEST_SOURCES})
target_link_libraries(tester PUBLIC
    arbimath_core
    GTest::GTest)
