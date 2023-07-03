cmake_minimum_required(VERSION 3.10)
project(Strava_Data_Visualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the necessary include directories
include_directories(include)

# Add the source files
set(SOURCES src/main.cpp)

# Add the required libraries
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
set(LIBS ${CURL_LIBRARIES})

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

