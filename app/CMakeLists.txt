find_package(OpenCV)

add_executable(human-tracker main.cpp AutoBot.cpp Detector.cpp HumanTracker.cpp Utils.cpp)
include_directories(
	${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE HEADER_FILES include/*.h include/*.hpp)
file(GLOB_RECURSE SOURCES src/*.c src/*.cpp src/*.h src/*.hpp)
