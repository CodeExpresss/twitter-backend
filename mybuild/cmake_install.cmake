# Install script for directory: /home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/data_base/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/models/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/repositories/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/controllers/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/unit_of_work/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/server/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/client/cmake_install.cmake")
  include("/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/test/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
