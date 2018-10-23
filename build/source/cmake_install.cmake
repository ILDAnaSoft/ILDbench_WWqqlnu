# Install script for directory: /afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/source

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/gear/v01-08/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CLHEP/2.3.4.3/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/ilcutil/v01-05/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinUtil/v01-15/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/CED/v01-09-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/root/6.08.06/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/build/lib/libILDbench_WWqqlnu.so.1.0.0"
    "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/build/lib/libILDbench_WWqqlnu.so.1.0"
    "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/build/lib/libILDbench_WWqqlnu.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so.1.0.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libILDbench_WWqqlnu.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/gear/v01-08/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CLHEP/2.3.4.3/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/ilcutil/v01-05/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinUtil/v01-15/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/CED/v01-09-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/root/6.08.06/lib:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/afs/desy.de/user/a/anguiano/work/repos/ILDbench_WWqqlnu/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/Marlin/v01-16/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/gear/v01-08/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/CLHEP/2.3.4.3/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/ilcutil/v01-05/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/DD4hep/v01-07-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinUtil/v01-15/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/CED/v01-09-02/lib:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/root/6.08.06/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

