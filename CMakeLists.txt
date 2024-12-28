cmake_minimum_required(VERSION 3.5)
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
# find_package(GLEW REQUIRED)
# find_package(GLU REQUIRED)
# find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
#   message(STATUS "GLEW found: ${GLEW_INCLUDE_DIRS}")
  target_include_directories(${EXE_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
  target_link_libraries(${EXE_NAME} PRIVATE GLEW::GLEW)
endif()
find_package(FreeGLUT CONFIG REQUIRED)
if(FreeGLUT_FOUND)
#   message(STATUS "FreeGLUT found")
  target_link_libraries(${EXE_NAME} PRIVATE FreeGLUT::freeglut)
endif()
# Link the libraries to the target
target_link_libraries(${EXE_NAME} PRIVATE OpenGL::GL GLU GLEW)
# target_link_libraries(${EXE_NAME} PRIVATE ${GLUT_LIBRARIES})


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
