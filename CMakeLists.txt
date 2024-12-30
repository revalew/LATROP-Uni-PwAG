cmake_minimum_required(VERSION 3.10)
set(EXE_NAME latrop)
set(CMAKE_BUILD_TYPE Release)

project(${EXE_NAME})

# Define the folder containing source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Automatically gather all .cpp files in the src folder
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

# Create the executable from the automatically gathered source files
add_executable(${EXE_NAME} ${SOURCES})

# Find and link required libraries
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

# Link the libraries to the target
target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL GLU)

if(WIN32)
  # Windows-specific configurations
  # message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")
  # message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
  set(PKGPATH D:/a/LATROP-Uni-PwAG/LATROP-Uni-PwAG/vcpkg/packages)
  # list(APPEND CMAKE_PREFIX_PATH "D:/a/LATROP-Uni-PwAG/LATROP-Uni-PwAG/vcpkg/packages/glew_x64-windows/")
  list(APPEND CMAKE_PREFIX_PATH ${PKGPATH})
  find_package(GLEW REQUIRED)
  target_compile_definitions(${EXE_NAME} PRIVATE GLEW_BUILD)
  target_include_directories(${EXE_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
  target_link_libraries(${EXE_NAME} PRIVATE ${GLEW_LIBRARIES})
  target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL GLU GLEW::GLEW GLUT::GLUT)
  target_link_libraries(engine PUBLIC GLEW::GLEW)
else()
    # Linux-specific configurations
    target_link_libraries(${EXE_NAME} PRIVATE ${GLEW_LIBRARIES})
    target_link_libraries(${EXE_NAME} PRIVATE GLEW::GLEW)
    target_link_libraries(${EXE_NAME} PRIVATE ${GLUT_LIBRARIES})
    target_link_libraries(${EXE_NAME} PRIVATE GLUT::GLUT)
    target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL GLU GLEW::GLEW GLUT::GLUT)
endif()


# Add a custom target to run the executable
add_custom_target(run COMMAND ./${EXE_NAME})

# Copy resources (data and maps folders) after the build process
add_custom_command(
    TARGET ${EXE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/data ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/maps ${CMAKE_BINARY_DIR}/maps
)
