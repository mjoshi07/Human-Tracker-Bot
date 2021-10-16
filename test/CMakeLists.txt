set(GTEST_SHUFFLE 1)
find_package(OpenCV)

add_executable(
    human-tracker-test
    main.cpp
    test.cpp
    ../app/AutoBot.cpp
    ../app/HumanTracker.cpp
    ../app/Detector.cpp
    ../app/Utils.cpp
)

target_include_directories(human-tracker-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include
					${OpenCV_INCLUDE_DIRS})
target_link_libraries(human-tracker-test PUBLIC gtest ${OpenCV_LIBS})

