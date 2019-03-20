cmake_minimum_required(VERSION 3.7.2...3.14)

project(JsonBox)

include(GenerateExportHeader)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)
cmake_policy(SET CMP0063 NEW)

set(JSONBOX_SOURCES
  src/JsonWritingError.cpp
  src/Value.cpp
  src/SolidusEscaper.cpp
  src/Escaper.cpp
  src/Indenter.cpp
  src/IndentCanceller.cpp
  src/JsonParsingError.cpp
  src/Convert.cpp
)

set(JSONBOX_HEADERS
  include/JsonBox/Convert.h
  include/JsonBox/Escaper.h
  include/JsonBox/Grammar.h
  include/JsonBox/IndentCanceller.h
  include/JsonBox/Indenter.h
  include/JsonBox/JsonParsingError.h
  include/JsonBox/JsonWritingError.h
  include/JsonBox/OutputFilter.h
  include/JsonBox/SolidusEscaper.h
  include/JsonBox/Value.h
  include/JsonBox.h
)

# set options for android
if(CMAKE_SYSTEM_NAME MATCHES "Android")
	message("-- Compiling for Android")
    set(BUILD_SHARED_LIBS TRUE)
    if (CMAKE_ANDROID_API LESS 14)
        message(FATAL_ERROR "Android API level (${CMAKE_ANDROID_API}) must be equal or greater than 14.")
    endif()
    if(CMAKE_VS_PLATFORM_NAME STREQUAL "Tegra-Android")
        message(WARNING "CMake might not properly support setting the STL. Make sure to adjust all generated library projects!")
    endif()
	set(ANDROID_NDK "$ENV{ANDROID_NDK}")
    set(CMAKE_INSTALL_PREFIX ${CMAKE_ANDROID_NDK}/sources/third_party/jsonbox)
    set(DEFAULT_INSTALL_MISC_DIR ${CMAKE_ANDROID_NDK}/sources/third_party/jsonbox)
    set(LIB_SUFFIX "/${CMAKE_ANDROID_ARCH_ABI}")
    if(CMAKE_ANDROID_STL_TYPE MATCHES "_shared")
        add_definitions("-DSTL_LIBRARY=${CMAKE_ANDROID_STL_TYPE}")
        if(NOT CMAKE_ANDROID_STL_TYPE MATCHES "c\\+\\+_shared")
            message("Android: Using ${CMAKE_ANDROID_STL_TYPE} as STL. Set CMAKE_ANDROID_STL_TYPE to c++_shared, if there are any issues.")
        endif()
    else()
        message(WARNING "Android: You're using a static STL (${CMAKE_ANDROID_STL_TYPE}). Set CMAKE_ANDROID_STL_TYPE to c++_shared, if there are any issues.")
    endif()
	install(FILES src/Android.mk DESTINATION .)
endif(CMAKE_SYSTEM_NAME MATCHES "Android")

# build library
set(CMAKE_DEBUG_POSTFIX "_d")
if(NOT BUILD_SHARED_LIBS)
	add_library(JsonBox STATIC ${JSONBOX_SOURCES} ${JSONBOX_HEADERS})
else()
	add_library(JsonBox SHARED ${JSONBOX_SOURCES} ${JSONBOX_HEADERS})
endif()

generate_export_header(JsonBox EXPORT_FILE_NAME Export.h)

target_include_directories(JsonBox PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}
)
target_include_directories(JsonBox SYSTEM INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
)

export(TARGETS JsonBox
  FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
)

# Macro used to install headers while keeping the directory hierarchy.
MACRO(INSTALL_HEADERS_WITH_DIRECTORY HEADER_LIST)
  FOREACH(HEADER ${${HEADER_LIST}})
    STRING(REGEX MATCH "(.*)[/\\]" DIR ${HEADER})
	INSTALL(FILES ${HEADER} COMPONENT dev DESTINATION ${DIR})
  ENDFOREACH(HEADER)
ENDMACRO(INSTALL_HEADERS_WITH_DIRECTORY)

# install
install(TARGETS JsonBox
  COMPONENT lib
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

INSTALL_HEADERS_WITH_DIRECTORY(JSONBOX_HEADERS)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Export.h
  COMPONENT dev
  DESTINATION include/JsonBox
)
install(EXPORT ${PROJECT_NAME}
  DESTINATION lib${LIB_SUFFIX}/cmake
  FILE ${PROJECT_NAME}Config.cmake
)


# examples
add_executable(example1 "${CMAKE_CURRENT_SOURCE_DIR}/examples/main.cpp")
add_dependencies(example1 JsonBox)
target_link_libraries(example1 JsonBox)
