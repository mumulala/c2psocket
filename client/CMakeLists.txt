cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(csocket)


#set(-DCMAKE_BUILD_TYPE Release)
#cmake_policy(SET CMP0054 OLD)
set(OpenCV_DIR "E:\\opencv\\build")
MESSAGE("OpenCV_DIR: ${OpenCV_DIR}")

find_package( OpenCV 3.4.1 EXACT REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_definitions(-DOPENCV)



#find_package(Torch REQUIRED)



aux_source_directory(. DIR_SRCS)


add_executable(csocket ${DIR_SRCS})



target_link_libraries(csocket "${OpenCV_LIBS}")

set_property(TARGET csocket PROPERTY CXX_STANDARD 11)
