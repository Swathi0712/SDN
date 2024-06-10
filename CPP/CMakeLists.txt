cmake_minimum_required(VERSION 3.12)

# Set the CMake policy CMP0091 to NEW
if(POLICY CMP0091)
  cmake_policy(SET CMP0091 NEW)
endif()

project(MyProject)


set(CMAKE_CXX_STANDARD 11)
set(INCLUDE_PATHS cpp-httplib json/single_include/nlohmann)

# Include the Conan generated toolchain file
# include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Add source files
add_executable(MyProject src/main.cpp)

# Find and link Crow
# find_package(crow REQUIRED)
# find_package(asio REQUIRED)

# Set _WIN32_WINNT definition
# add_definitions(-D_WIN32_WINNT=0x0601)

# target_link_libraries(MyProject crow::crow asio::asio)
# Debug: Print Conan include directories
# message(STATUS "Conan include directories: ${CONAN_INCLUDE_DIRS}")
# target_include_directories(MyProject PRIVATE ${CONAN_INCLUDE_DIRS})
# target_include_directories(MyProject PRIVATE ${CMAKE_BINARY_DIR}/conan/include)
target_include_directories(MyProject PUBLIC  ${INCLUDE_PATHS})


# Debug: Print Conan libraries
# message(STATUS "Conan libraries: ${CONAN_LIBS}")
# target_link_libraries(MyProject ${CONAN_LIBS})

# target_link_libraries(MyProject Crow::Crow)
# target_link_libraries(MyProject asio::asio)
# target_link_libraries(MyProject PRIVATE ${CMAKE_BINARY_DIR}/conan/lib/asio.lib)
# target_link_libraries(MyProject PRIVATE ${CMAKE_BINARY_DIR}/conan/lib/crow.lib)
