cmake_minimum_required(VERSION 2.8)
project( OpenGLWithSound )

set( ExecName openglwithsound )

#----------------------------------------
# Use Qt 5
find_package( Qt5 COMPONENTS Widgets OpenGL Multimedia REQUIRED )
include_directories( ${Qt5Widgets_INCLUDE_DIRS} )
include_directories( ${Qt5OpenGL_INCLUDE_DIRS} )
include_directories( ${Qt5Multimedia_INCLUDE_DIRS} )
#----------------------------------------

#----------------------------------------
# Use Opengl
find_package(OpenGL)
#----------------------------------------

#----------------------------------------
# Use lib audiodecoder and CoreAudio 
find_library( audiodecoder_lib audiodecoder )
find_path( audiodecoder_include_dir audiodecoder.h )
include_directories( ${audiodecoder_include_dir} )
find_library( coreaudio_framework CoreAudio ) 
include_directories( ${coreaudio_framework}/Headers/ )

# Set flags to make a bundle on MAC
if(APPLE)
  SET(EXECUTABLE_FLAG MACOSX_BUNDLE)
endif(APPLE)

set( proj_src  main.cpp 
		mainwidget.cpp 
		openglwidget.cpp )

set( proj_hdr mainwidget.h 
		openglwidget.h )

# Include bin directory for moc files
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create classes from Qt ui files
set( proj_ui mainwidget.ui )
qt5_wrap_ui( proj_hdr_ui ${proj_ui} )

# moc Qt source file without a ui file
qt5_wrap_cpp( proj_moc ${proj_hdr})

set( proj_all_src ${proj_src} ${proj_hdr} ${proj_moc} ${proj_hdr_ui} )
add_executable( ${ExecName} ${EXECUTABLE_FLAG} ${proj_all_src} )
target_link_libraries( ${ExecName} ${OPENGL_gl_LIBRARY} ${QT_LIBRARIES} ${audiodecoder_lib} ${coreaudio_framework} )
qt5_use_modules( ${ExecName} Widgets OpenGL Multimedia )

