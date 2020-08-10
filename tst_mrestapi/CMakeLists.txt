find_package(Qt5 COMPONENTS REQUIRED Core Network Test)

set(CMAKE_AUTOMOC ON)

set(TEST_SRC
    restapiclient.h
    restapiclient.cpp
    testrequest.h
    testrequest.cpp
    weatherbycitynamerequest.h
    weatherbycitynamerequest.cpp
    tst_mrestapi.cpp
)

add_executable(mrestapi_test ${TEST_SRC})

target_link_libraries(mrestapi_test mrestapi
  Qt5::Core Qt5::Network Qt5::Test
)

add_test(mrestapi_test mrestapi_test)
