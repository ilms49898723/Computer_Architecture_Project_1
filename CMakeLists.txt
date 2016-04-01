cmake_minimum_required(VERSION 3.5)
project(Computer_Architecture_Project_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    .settings/org.eclipse.cdt.managedbuilder.core.prefs
    .cproject
    .gitignore
    .project
    InstDataBin.cpp
    InstDataBin.h
    InstDataStr.cpp
    InstDataStr.h
    InstDecode.cpp
    InstDecode.h
    InstEnum.h
    InstErrorDetector.cpp
    InstErrorDetector.h
    InstImageReader.cpp
    InstImageReader.h
    InstLookUp.cpp
    InstLookUp.h
    InstMemory.cpp
    InstMemory.h
    InstSimulator.cpp
    InstSimulator.h
    InstUtility.cpp
    InstUtility.h
    main.cpp
    makefile
    README.md)

add_executable(Computer_Architecture_Project_1 ${SOURCE_FILES})