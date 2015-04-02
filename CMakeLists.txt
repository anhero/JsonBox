cmake_minimum_required(VERSION 2.6)

project(JsonBox)

# glob all sources
file(GLOB_RECURSE JSONBOX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src" "src/*.cpp")
file(GLOB_RECURSE JSONBOX_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include" "include/*.h")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# setup static archive
set(CMAKE_DEBUG_POSTFIX "_d")
add_library(JsonBox ${JSONBOX_SOURCES} ${JSONBOX_HEADERS})

# install
install(TARGETS JsonBox
  COMPONENT lib
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  RUNTIME DESTINATION bin
)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION "include" COMPONENT dev)

# examples
add_executable(example1 "${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp")
add_dependencies(example1 JsonBox)
target_link_libraries(example1 JsonBox)
