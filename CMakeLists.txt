cmake_minimum_required(VERSION 2.6)

project(JsonBox)

set(JSONBOX_SOURCES
  src/JsonWritingError.cpp
  src/Value.cpp
  src/Array.cpp
  src/SolidusEscaper.cpp
  src/Escaper.cpp
  src/Indenter.cpp
  src/IndentCanceller.cpp
  src/JsonParsingError.cpp
  src/Convert.cpp
  src/Object.cpp
)
set(JSONBOX_HEADERS
  include/JsonBox/Array.h
  include/JsonBox/Convert.h
  include/JsonBox/Escaper.h
  include/JsonBox/Grammar.h
  include/JsonBox/IndentCanceller.h
  include/JsonBox/Indenter.h
  include/JsonBox/JsonParsingError.h
  include/JsonBox/JsonWritingError.h
  include/JsonBox/Object.h
  include/JsonBox/OutputFilter.h
  include/JsonBox/SolidusEscaper.h
  include/JsonBox/Value.h
  include/JsonBox.h
)

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
