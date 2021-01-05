cmake_minimum_required(VERSION 3.14)

project(Bustout)

add_subdirectory(vendor)

set(
	main_sources
		src/main.cpp
)

add_executable(
	Bustout
		${main_sources}
)

set_target_properties(Bustout PROPERTIES CXX_STANDARD 17)

source_group(main FILES ${main_sources})

macro(add_sfml_dependency my_target sfml_target)
	add_custom_command(
		TARGET ${my_target}
		PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			$<TARGET_FILE:${sfml_target}>
			$<TARGET_FILE_DIR:${my_target}>/$<TARGET_FILE_NAME:${sfml_target}>
	)

	target_link_libraries(
		${my_target}
			PRIVATE
				${sfml_target}
	)
endmacro()

add_sfml_dependency(Bustout sfml-graphics)
add_sfml_dependency(Bustout sfml-window)
add_sfml_dependency(Bustout sfml-system)

target_link_libraries(
	Bustout
		PRIVATE
			box2d
)

target_compile_definitions(Bustout PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/assets")

# set max warning level and VS startup project
if(MSVC)
	add_compile_options(/W4 /WX)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bustout)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()