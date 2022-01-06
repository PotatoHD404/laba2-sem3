#add_subdirectory(/usr/src/gtest [binary_dir])
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#include(GoogleTest)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
set(CMAKE_CXX_FLAGS "-Wno-gnu-zero-variadic-macro-arguments")

add_executable(Tests
        ArraySequenceTests.cpp
        ComplexTests.cpp
        DynamicArrayTests.cpp
        LinkedListTests.cpp
        ListSequenceTests.cpp
        SortTests.cpp SetTests.cpp)


include(GoogleTest)
target_link_libraries(Tests gtest_main)