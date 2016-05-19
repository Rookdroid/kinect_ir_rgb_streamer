cmake_minimum_required(VERSION 2.8.3)
project(kinect_ir_rgb_streamer)

find_package (
	catkin REQUIRED COMPONENTS
	roscpp
	rospy
	std_msgs
	tf
	cv_bridge
	image_transport
)

#add_message_files (
#	DIRECTORY msg
#	FILES
#)

#add_service_files (
#	DIRECTORY srv
#	FILES
#	
#)

#generate_messages(
#	DEPENDENCIES
#	std_msgs
#)

catkin_package(
	INCLUDE_DIRS include include/kinect_ir_rgb_streamer 
	CATKIN_DEPENDS 
)

include_directories( 
	include
	${catkin_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)


add_executable (
	kinect_ir_rgb_streamer 
	src/kinect_ir_rgb_streamer.cpp 
)

#add_dependencies(
#	kinect_ir_rgb_streamer 
#)

target_link_libraries (
	kinect_ir_rgb_streamer 
	${catkin_LIBRARIES}
	${OpenCV_LIBRARIES}
)

