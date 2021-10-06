add_executable(human-tracker main.cpp AutoBot.cpp Detector.cpp HumanTracker.cpp Utils.cpp)
include_directories(
	${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries (human-tracker ${OpenCV_LIBS})
