add_subdirectory(debug)
add_subdirectory(gfx)
add_subdirectory(scenes)
add_subdirectory(ui)
add_subdirectory(game)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
	main_sources
		main.cpp
		
		maths.h
		
		Layer.h
		Layer.cpp
)



add_executable(
	Bustout
		${main_sources}
		${gfx_sources}
		${scenes_sources}
		${ui_sources}
		${game_sources}
		$<$<CONFIG:Debug>:${debug_sources}>
)

set_target_properties(Bustout PROPERTIES CXX_STANDARD 17)

source_group(main FILES ${main_sources})
source_group(gfx FILES ${gfx_sources})
source_group(scenes FILES ${scenes_sources})
source_group(ui FILES ${ui_sources})
source_group(game FILES ${game_sources})
source_group(debug FILES $<$<CONFIG:Debug>:${debug_sources}>)

target_include_directories(Bustout PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

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

target_compile_definitions(Bustout PRIVATE ASSET_DIR="${CMAKE_SOURCE_DIR}/assets" $<$<CONFIG:Debug>:BUSTOUT_DEBUG>)

# set max warning level and VS startup project
if(MSVC)
	add_compile_options(/W4 /WX)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Bustout)
else()
	add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()