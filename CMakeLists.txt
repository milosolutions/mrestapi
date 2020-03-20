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

set(SOURCES mrestrequest.h
  mrestrequestqueue.h
  mrestrequestmanager.h
  mrestrequestptr.h
  mrestrequest.cpp
  mrestrequestqueue.cpp
  mrestrequestmanager.cpp
)

set(OTHER_FILES README.md AUTHORS.md mrestapi.doxyfile)

add_library(mrestapi OBJECT ${SOURCES} ${OTHER_FILES})

option (production-server "MRestApi: Use production server" OFF)
if (production-server)
  target_compile_definitions(mrestapi PUBLIC USE_PRODUCTION_SERVER)
endif ()

target_include_directories(mrestapi
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(mrestapi
  Qt5::Core
  Qt5::Network
)

enable_testing()
add_subdirectory(tst_mrestapi)
add_test(NAME MRestApiTest COMMAND mrestapi_test)
