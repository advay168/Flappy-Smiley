cmake_minimum_required( VERSION 3.1 )

project( Flappy_Smiley )

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

add_subdirectory( glfw )

if( MSVC )
    # SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set(SRC Application.cpp Bird.cpp Bird.h Constants.h Draw.cpp Draw.h Game.cpp Game.h GameObject.h Pipe.cpp Pipe.h Shader.cpp Shader.h Texture.cpp Texture.h)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/includes/*.h ${CMAKE_SOURCE_DIR}/includes/*.hpp)

include_directories("includes")

include_directories("glm")

file(GLOB third_party third_party_source/*)
     
add_executable( Flappy_Smiley ${SRC} ${third_party})
target_link_libraries( Flappy_Smiley glfw )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0") 
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Flappy_Smiley )
    endif()
endif()

add_custom_command(TARGET Flappy_Smiley POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)