cmake_minimum_required(VERSION 2.8.3)
project(gtec_rosrtls)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")

#message( ${CMAKE_CURRENT_SOURCE_DIR} )
message( ${CMAKE_MODULE_PATH} )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -pthread")

add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  gtec_msgs
)

## System dependencies are found with CMake's conventions

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system)

find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

find_package(Restclient-cpp REQUIRED)
include_directories(${LIBRESTCLIENT_CPP_INCLUDE_DIRS})

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
include_directories($CURL_INCLUDE_DIRS)


## Generate messages in the 'msg' folder
#add_message_files(
#  FILES
# )

## Generate added messages and services with any dependencies listed here
#generate_messages(
#  DEPENDENCIES
#  std_msgs
#)

catkin_package(
)

###########
## Build ##
###########


include_directories(src/rosrtls/messages)
include_directories(src/rosrtls/publishers)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

set(SOURCE_FILES_RANGING src/rosrtls/publishers/node_ranging.cpp
    src/rosrtls/messages/rtls_ranging.cpp)

set(SOURCE_FILES_POSE src/rosrtls/publishers/node_pose.cpp
    src/rosrtls/messages/rtls_pose.cpp)


## Declare a cpp executable

add_executable(rtlsranging ${SOURCE_FILES_RANGING})
target_link_libraries(rtlsranging
   ${catkin_LIBRARIES}
   ${LIBRESTCLIENT_CPP_LIBRARIES}
   ${CURL_LIBRARIES}
 )
add_dependencies(rtlsranging ${catkin_EXPORTED_TARGETS})
add_dependencies(rtlsranging gtec_msgs_generate_messages_cpp)


add_executable(rtlspose ${SOURCE_FILES_POSE})
target_link_libraries(rtlspose
   ${catkin_LIBRARIES}
   ${LIBRESTCLIENT_CPP_LIBRARIES}
   ${CURL_LIBRARIES}
 )
add_dependencies(rtlspose ${catkin_EXPORTED_TARGETS})
add_dependencies(rtlspose gtec_msgs_generate_messages_cpp)
