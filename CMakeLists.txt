if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif ()

cmake_minimum_required(VERSION 3.5)

project(mrestapi
  VERSION 0.0.1
  DESCRIPTION "Milo Rest API"
  LANGUAGES CXX
)

find_package(Qt5 COMPONENTS REQUIRED Core Network)

set(CMAKE_AUTOMOC ON)

set(SOURCES
  mrestrequest.h
  mrestrequestptr.h
  mrestrequest.cpp
  mrestrequestqueue.h
  mrestrequestqueue.cpp
  mrestrequestmanager.h
  mrestrequestmanager.cpp
  mimagerequest.h
  mimagerequest.cpp
  mmultipartrequest.h
  mmultipartrequest.cpp
)

set(OTHER_FILES README.md AUTHORS.md mrestapi.doxyfile)

add_library(mrestapi STATIC ${SOURCES} ${OTHER_FILES})

option (production-server "MRestApi: Use production server" OFF)
if (production-server)
  target_compile_definitions(mrestapi PUBLIC USE_PRODUCTION_SERVER)
endif ()

target_include_directories(mrestapi
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(mrestapi
  Qt5::Core
  Qt5::Network
)

add_subdirectory(tst_mrestapi)
#add_subdirectory(example)
