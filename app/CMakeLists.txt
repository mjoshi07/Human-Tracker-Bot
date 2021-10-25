find_package(Eigen3 REQUIRED)

add_executable(human-tracker main.cpp AutoBot.cpp Detector.cpp HumanTracker.cpp Utils.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    	${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(human-tracker PUBLIC ${OpenCV_LIBS} ${EIGEN3_LIBS})
