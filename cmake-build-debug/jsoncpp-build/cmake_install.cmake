# Install script for directory: C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/3rdparty/jsoncpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/boost")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/pkg-config/jsoncpp.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp/jsoncppConfig.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp/jsoncppConfig.cmake"
         "C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/CMakeFiles/Export/lib/cmake/jsoncpp/jsoncppConfig.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp/jsoncppConfig-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp/jsoncppConfig.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp" TYPE FILE FILES "C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/CMakeFiles/Export/lib/cmake/jsoncpp/jsoncppConfig.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp" TYPE FILE FILES "C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/CMakeFiles/Export/lib/cmake/jsoncpp/jsoncppConfig-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/jsoncpp" TYPE FILE FILES "C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/jsoncppConfigVersion.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/src/cmake_install.cmake")
  include("C:/Users/luoyuchu/Desktop/Currrent_Semester/CompilerProject-2020Spring/cmake-build-debug/jsoncpp-build/include/cmake_install.cmake")

endif()

