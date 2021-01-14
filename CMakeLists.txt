cmake_minimum_required(VERSION 3.14)

project(Bustout)

add_subdirectory(vendor)

add_subdirectory(src)

# set max warning level and VS startup project
if(MSVC)
	add_compile_options(/W4 /WX)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bustout)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()