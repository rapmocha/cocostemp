# Copyright 2016 rapmocha

#### Configure meta data
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(CocosTemplate)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)

#### Set directory
set(CPPLINT /usr/local/mybin/cpplint.py)
set(SOURCES_DIR_REL source)
set(INCLUDE_DIR_REL include)
set(RESOURCES_DIR_REL Resources)
set(COCOS2D_DIR /usr/local/myinclude/cocos2d)
set(COCOS_DIR ${COCOS2D_DIR}/cocos)
set(GLFW3_INCLUDE_DIRS ${COCOS2D_DIR}/external/glfw3/include/mac)
set(COCOS2D_LIB_DIR /usr/local/mylib)
set(COCOS2D_LIBRARY
  cocos2dMac3.8
  )
set(SOURCES_DIR ${PROJECT_SOURCE_DIR}/${SOURCES_DIR_REL})
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/${INCLUDE_DIR_REL})
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/${RESOURCES_DIR_REL})
set(EXCLUDE_CPPLINT_SOURCES
  ${SOURCES_DIR}/main.cpp
  ${SOURCES_DIR}/AppDelegate.cpp
  ${INCLUDE_DIR}/AppDelegate.h
  )
message([Project name]: ${PROJECT_NAME})
message([Project source dir]: ${PROJECT_SOURCE_DIR})
message([Build binary dir]: ${CMAKE_BINARY_DIR})
message([Include headers dir]: "(project root)/${INCLUDE_DIR_REL}")
message([Sources dir]: "(project root)/${SOURCES_DIR_REL}")
message([Resources dir]: "(project root)/${RESOURCES_DIR_REL}")
message([cpplint path]: ${CPPLINT})

#### Create directory for app bundle
file(MAKE_DIRECTORY
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/MacOS
  )

#### Symlink resources directory
if(NOT EXISTS ${PROJECT_NAME}.app/Contents/${RESOURCES_DIR_REL})
  execute_process(COMMAND ln -s ${RESOURCES_DIR} ${PROJECT_NAME}.app/Contents/)
  message(Symlinked resources to build dir: ${RESOURCES_DIR_REL})
else()
  message(Symlinked resources to build dir: ${RESOURCES_DIR_REL} (already exists))
endif()

#### Specify link directories
# add_executableよりも先に置く。
link_directories(/usr/local/mylib/)

#### Find source files
# GLOB_RECURSE:    ファイルを再帰的に探索する。
# INCLUDES:        ヘッダファイル
# SOURCES:         ソースファイル
# EXCLUDE_SOURCES: ビルドしないソースファイル
file(GLOB_RECURSE INCLUDES ${INCLUDE_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${SOURCES_DIR}/*.cpp)
file(GLOB_RECURSE EXCLUDE_SOURCES "foo.cpp")
list(REMOVE_ITEM SOURCES "${EXCLUDE_SOURCES}")
add_executable(${PROJECT_NAME} ${SOURCES})

#### Specify include header directories
include_directories(${INCLUDE_DIR})
include_directories(/System/Library/Frameworks)
include_directories(${COCOS_DIR})
include_directories(${GLFW3_INCLUDE_DIRS})

#### Specify Libraries
find_library(COCOA_LIBRARY Cocoa)
find_library(OPENGL_LIBRARY OpenGL)
find_library(AUDIOTOOLBOX_LIBRARY AudioToolbox)
find_library(OPENAL_LIBRARY OpenAL)
find_library(QUARTZCORE_LIBRARY QuartzCore)
find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices)
find_library(IOKIT_LIBRARY IOKit)
find_library(FOUNDATION_LIBRARY Foundation)
find_library(Z_LIBRARY Z)
find_library(ICONV_LIBRARY Iconv)
target_link_libraries(${PROJECT_NAME}
  ${COCOA_LIBRARY}
  ${OPENGL_LIBRARY}
  ${OPENAL_LIBRARY}
  ${AUDIOTOOLBOX_LIBRARY}
  ${QUARTZCORE_LIBRARY}
  ${APPLICATIONSERVICES_LIBRARY}
  ${IOKIT_LIBRARY}
  ${FOUNDATION_LIBRARY}
  ${Z_LIBRARY}
  ${ICONV_LIBRARY}
  ${COCOS2D_LIBRARY}
  )

#### Set compiler option
# C++11拡張を有効にする。
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

#### Other targets
# run
add_custom_target(run DEPENDS ${PROJECT_NAME}
  COMMAND cp ${PROJECT_NAME} ${PROJECT_NAME}.app/Contents/MacOS/
  COMMENT copy ${PROJECT_NAME} to app contents
  COMMAND open ${PROJECT_NAME}.app
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )


# cpplint
# cpplintは、.gitのある${PROJECT_SOURCE_DIR}から
# 実行しないと--rootオプションが効かず、
# [build/header_guard]がおかしくなる。
set(CPPLINT_SOURCE ${SOURCES} ${INCLUDES})
foreach(i ${EXCLUDE_CPPLINT_SOURCES})
  list(REMOVE_ITEM CPPLINT_SOURCE "${i}")
endforeach(i)
add_custom_target(cpplint
  COMMAND ${CPPLINT} --root=${INCLUDE_DIR_REL} ${CPPLINT_SOURCE}
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )

