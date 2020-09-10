cmake_minimum_required(VERSION 3.0.0)
project(gstreamer-tutorial-11 VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED on)


include(CTest)
enable_testing()

include(FindPkgConfig)
if(PKG_CONFIG_FOUND)
    message(PKG_CONFIG_FOUND : ${PKG_CONFIG_FOUND})
    pkg_check_modules ( GST gstreamer-1.0 )
    pkg_check_modules ( GLIB glib-2.0 )

    message(GST_INCLUDE_DIRS : ${GST_INCLUDE_DIRS})
    message(GST_LIBRARY_DIRS : ${GST_LIBRARY_DIRS})
    message(GST_LIBRARIES : ${GST_LIBRARIES})
    message(GLIB_INCLUDE_DIRS : ${GLIB_INCLUDE_DIRS})
    message(GLIB_LIBRARY_DIRS : ${GLIB_LIBRARY_DIRS})
    message(GLIB_LIBRARIES : ${GLIB_LIBRARIES})

    include_directories(${GST_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})
    link_libraries(${GST_LIBRARIES} ${GLIB_LIBRARIES})
endif()



add_executable(gstreamer-tutorial-11-1 main1.cpp)
add_executable(gstreamer-tutorial-11-2 main2.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
