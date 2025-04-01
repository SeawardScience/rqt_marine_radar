cmake_minimum_required(VERSION 3.14.4)
project(rqt_marine_radar)

#add_compile_options(-std=c++11)

set(ROS_DEPENDS
  ament_cmake
  rclcpp
  qt_gui_cpp
  rqt_gui_cpp
  ament_lint_auto
  marine_radar_control_msgs
  marine_sensor_msgs
)

set(EXTERNAL_DEPENDS
  Qt5Widgets
)

set(EXTERNAL_DEPENDS_LIB 

)

get_filename_component(PACKAGE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
message("Creating Package: ${PACKAGE_NAME}")
project(${PACKAGE_NAME})  ## this package name is the name of the directory this cmake file is in

add_compile_definitions(CMAKE_PACKAGE_NAME=${PACKAGE_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Default to C++17 for humble
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

###
###  Add dependencies
###

foreach(DEPEND ${ROS_DEPENDS} ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)

set(rqt_marine_radar_SRCS
    src/rqt_marine_radar/marine_radar_plugin.cpp
    src/rqt_marine_radar/radar_widget.cpp
)

set(rqt_marine_radar_HDRS
    include/rqt_marine_radar/marine_radar_plugin.h
    include/rqt_marine_radar/radar_widget.h
)

set(rqt_marine_radar_UIS
    src/rqt_marine_radar/marine_radar_plugin.ui
)

qt5_wrap_cpp(rqt_marine_radar_MOCS ${rqt_marine_radar_HDRS})
qt5_wrap_ui(rqt_marine_radar_UIS_H ${rqt_marine_radar_UIS})

add_library(${PROJECT_NAME} SHARED
    ${rqt_marine_radar_SRCS}
    ${rqt_marine_radar_MOCS}
    ${rqt_marine_radar_UIS_H}
)

target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/${PROJECT_NAME}>"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  ${rclcpp_TARGETS}
  ${qt_gui_cpp_TARGETS}
  ${rqt_gui_cpp_TARGETS}
  ${marine_sensor_msgs_TARGETS}
  ${marine_radar_control_msgs_TARGETS}
  Qt5::Widgets
)

##################
## INSTALLATION ##
##################

message("  Installing: " ${EXECUTABLES})

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION bin/${PROJECT_NAME}
)

install(PROGRAMS scripts/rqt_marine_radar
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

install(FILES
  plugin.xml
  DESTINATION share/${PROJECT_NAME}
)

pluginlib_export_plugin_description_file(rqt_gui "plugin.xml")

#############
## testing ##
#############

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
