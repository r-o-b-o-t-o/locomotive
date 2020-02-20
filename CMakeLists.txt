CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(locomotive VERSION 0.1.0)
SET(CMAKE_CXX_STANDARD 17)

# Includes
INCLUDE_DIRECTORIES(include lib/glad/include)
SET(include_list
    include/locomotive/arena.h
    include/locomotive/camera.h
    include/locomotive/components.h
    include/locomotive/components/component.h
    include/locomotive/components/spherecollider.h
    include/locomotive/components/transform.h
    include/locomotive/gameobject.h
    include/locomotive/locomotive.h
    include/locomotive/material.h
    include/locomotive/mesh.h
    include/locomotive/phong.h
    include/locomotive/shader.h
    include/locomotive/threadpool.h
    include/locomotive/window.h
    include/locomotive/scene.h
    include/locomotive/engine.h
)

# Sources
SET(sources_list
    src/camera.cpp
    src/component.cpp
    src/gameobject.cpp
    src/mesh.cpp
    src/material.cpp
    src/phong.cpp
    src/shader.cpp
    src/spherecollider.cpp
    src/transform.cpp
    src/window.cpp
    src/scene.cpp
    src/engine.cpp

    lib/glad/src/glad.c
)

# GLFW build options
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Dynamic library
ADD_LIBRARY(locomotive SHARED ${sources_list} ${include_list})

# Add flags
IF (WIN32)
    TARGET_COMPILE_DEFINITIONS(locomotive PRIVATE WINDOWS=1)
ENDIF ()
TARGET_COMPILE_DEFINITIONS(locomotive PRIVATE LOCOMOTIVE_EXPORTS=1)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Create VS filters based on sources directory structure
FOREACH (source IN LISTS sources_list)
    GET_FILENAME_COMPONENT(source_path "${source}" PATH)
    STRING(REPLACE "/" "\\" source_path_msvc "${source_path}")
    SOURCE_GROUP("${source_path_msvc}" FILES "${source}")
ENDFOREACH ()
FOREACH (header IN LISTS include_list)
    GET_FILENAME_COMPONENT(header_path "${header}" PATH)
    STRING(REPLACE "/" "\\" header_path_msvc "${header_path}")
    SOURCE_GROUP("${header_path_msvc}" FILES "${header}")
ENDFOREACH ()

# Libs
INCLUDE_DIRECTORIES(lib/OBJ_Loader/include)

ADD_SUBDIRECTORY(lib/glfw)
INCLUDE_DIRECTORIES(lib/glfw/include)
TARGET_INCLUDE_DIRECTORIES(locomotive PUBLIC ${glfw_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(locomotive glfw ${glfw_LIBRARIES})

FIND_PACKAGE(OpenGL REQUIRED)
TARGET_INCLUDE_DIRECTORIES(locomotive PUBLIC ${OPENGL_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(locomotive ${OPENGL_gl_LIBRARY})
