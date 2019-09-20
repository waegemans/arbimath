set(ARBIMATH_SOURCES
        arbimath/bigint/BigInt.cpp
        arbimath/bigint/VectorUtil.cpp
    )

add_library(arbimath_core STATIC ${ARBIMATH_SOURCES})
target_include_directories(arbimath_core PUBLIC ${CMAKE_SOURCE_DIR}/lib)

