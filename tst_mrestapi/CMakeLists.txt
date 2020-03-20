find_package(Qt5 COMPONENTS Core Network Test REQUIRED)

set(CMAKE_AUTOMOC ON)

set(TEST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/restapiclient.h
    ${CMAKE_CURRENT_SOURCE_DIR}/restapiclient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/testrequest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/testrequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/weatherbycitynamerequest.h
    ${CMAKE_CURRENT_SOURCE_DIR}/weatherbycitynamerequest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tst_mrestapi.cpp
)

set(APP_SRC
    ${PROJECT_SOURCE_DIR}/mrestrequestqueue.h
    ${PROJECT_SOURCE_DIR}/mrestrequestmanager.h
    ${PROJECT_SOURCE_DIR}/mrestrequestptr.h
    ${PROJECT_SOURCE_DIR}/mrestrequest.cpp
    ${PROJECT_SOURCE_DIR}/mrestrequestqueue.cpp
    ${PROJECT_SOURCE_DIR}/mrestrequestmanager.cpp
)

add_executable(mrestapi_test ${TEST_SRC} ${APP_SRC})

target_include_directories(mrestapi_test PRIVATE ${PROJECT_SOURCE_DIR})

qt5_use_modules(mrestapi_test Core Network Test)
